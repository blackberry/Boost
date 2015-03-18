// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR

#include <boost/range.hpp>

#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{


struct turn_get_box
{
    template <typename Box, typename Turn>
    static inline void apply(Box& total, Turn const& turn)
    {
        geometry::expand(total, turn.robust_point);
    }
};

struct turn_ovelaps_box
{
    template <typename Box, typename Turn>
    static inline bool apply(Box const& box, Turn const& turn)
    {
        return ! dispatch::disjoint
            <
                typename Turn::robust_point_type,
                Box
            >::apply(turn.robust_point, box);
    }
};

template <typename Turns, typename Pieces>
class turn_in_piece_visitor
{
    Turns& m_turns; // because partition is currently operating on const input only
    Pieces const& m_pieces; // to check for piece-type

    typedef boost::long_long_type calculation_type;

    template <typename Point>
    static inline bool projection_on_segment(Point const& subject, Point const& p, Point const& q)
    {
        typedef Point vector_type;
        typedef typename geometry::coordinate_type<Point>::type coordinate_type;

        vector_type v = q;
        vector_type w = subject;
        subtract_point(v, p);
        subtract_point(w, p);

        coordinate_type const zero = coordinate_type();
        coordinate_type const c1 = dot_product(w, v);

        if (c1 < zero)
        {
            return false;
        }
        coordinate_type const c2 = dot_product(v, v);
        if (c2 < c1)
        {
            return false;
        }

        return true;
    }

    template <typename Point, typename Piece>
    inline bool on_offsetted(Point const& point, Piece const& piece) const
    {
        typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Point>::type
            >::type side_strategy;
        geometry::equal_to<Point> comparator;

        for (int i = 1; i < piece.offsetted_count; i++)
        {
            Point const& previous = piece.robust_ring[i - 1];
            Point const& current = piece.robust_ring[i];

            // The robust ring contains duplicates, avoid applying side on them (will be 0)
            if (! comparator(previous, current))
            {
                int const side = side_strategy::apply(previous, current, point);
                if (side == 0)
                {
                    // Collinear, check if projection falls on it
                    if (projection_on_segment(point, previous, current))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    template <typename Point, typename Piece>
    static inline
    calculation_type comparable_distance_from_offsetted(Point const& point,
                        Piece const& piece)
    {
        // TODO: pass subrange to dispatch to avoid making copy
        geometry::model::linestring<Point> ls;
        std::copy(piece.robust_ring.begin(),
            piece.robust_ring.begin() + piece.offsetted_count,
            std::back_inserter(ls));
        typename default_comparable_distance_result<Point, Point>::type
            const comp = geometry::comparable_distance(point, ls);

        return static_cast<calculation_type>(comp);
    }

public:

    inline turn_in_piece_visitor(Turns& turns, Pieces const& pieces)
        : m_turns(turns)
        , m_pieces(pieces)
    {}

    template <typename Turn, typename Piece>
    inline void apply(Turn const& turn, Piece const& piece, bool first = true)
    {
        boost::ignore_unused_variable_warning(first);

        if (turn.count_within > 0)
        {
            // Already inside - no need to check again
            return;
        }

        if (piece.type == strategy::buffer::buffered_flat_end
            || piece.type == strategy::buffer::buffered_concave)
        {
            // Turns cannot be inside a flat end (though they can be on border)
            // Neither we need to check if they are inside concave helper pieces
            return;
        }

        bool neighbour = false;
        for (int i = 0; i < 2; i++)
        {
            // Don't compare against one of the two source-pieces
            if (turn.operations[i].piece_index == piece.index)
            {
                return;
            }

            typename boost::range_value<Pieces>::type const& pc
                                = m_pieces[turn.operations[i].piece_index];
            if (pc.left_index == piece.index
                || pc.right_index == piece.index)
            {
                if (pc.type == strategy::buffer::buffered_flat_end)
                {
                    // If it is a flat end, don't compare against its neighbor:
                    // it will always be located on one of the helper segments
                    return;
                }
                neighbour = true;
            }
        }

        int geometry_code = detail::within::point_in_geometry(turn.robust_point, piece.robust_ring);

        if (geometry_code == -1)
        {
            return;
        }
        if (geometry_code == 0 && neighbour)
        {
            return;
        }

        Turn& mutable_turn = m_turns[turn.turn_index];
        if (geometry_code == 0)
        {
            // If it is on the border and they are not neighbours, it should be
            // on the offsetted ring

            if (! on_offsetted(turn.robust_point, piece))
            {
                // It is on the border but not on the offsetted ring.
                // Then it is somewhere on the helper-segments
                // Classify it as "within"
                geometry_code = 1;
                mutable_turn.count_on_helper++; // can still become "near_offsetted"
            }
            else
            {
                mutable_turn.count_on_offsetted++; // value is not used anymore
            }
        }

        if (geometry_code == 1)
        {
            calculation_type const distance
                = comparable_distance_from_offsetted(turn.robust_point, piece);
            if (distance >= 4)
            {
                // This is too far from the border, it counts as "really within"
                mutable_turn.count_within++;
            }
            else
            {
                // Other points count as still "on border" because they might be
                // travelled through, but not used as starting point
                mutable_turn.count_within_near_offsetted++;
            }
        }
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR
