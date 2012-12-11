/// \file intersections.h

/*!
\def CGAL_INTERSECTION_VERSION

\ingroup intersection

The macro `CGAL_INTERSECTION_VERSION` can be used to configure
which version of the `intersection()` function should be used and
enables the corresponding APIs in other \cgal packages. It should be
defined before any \cgal header is included.

- `CGAL_INTERSECTION_VERSION == 1` `intersection()` uses `Object`
- `CGAL_INTERSECTION_VERSION == 2` `intersection()` uses `boost::optional< boost::variant< T... > >`

*/
#define CGAL_INTERSECTION_VERSION

namespace CGAL {

/*!
\addtogroup do_intersect

\brief 
\details Depending on which \cgal kernel is used, different overloads of this global
function are available.
*/

/*!
\addtogroup do_intersect_linear do_intersect (2D/3D Linear Kernel)
\ingroup do_intersect

\sa `intersection`
*/

/// @{
/*!
checks whether `obj1` and `obj2` intersect.  Two objects `obj1` and
`obj2` intersect if there is a point `p` that is part of both `obj1`
and `obj2`.  The intersection region of those two objects is defined
as the set of all points `p` that are part of both `obj1` and `obj2`.
Note that for objects like triangles and polygons that enclose a
bounded region, this region is part of the object.

The types `Type1` and `Type2` can be any of the following:

- `Point_2<Kernel>`
- `Line_2<Kernel>`
- `Ray_2<Kernel>`
- `Segment_2<Kernel>`
- `Triangle_2<Kernel>`
- `Iso_rectangle_2<Kernel>`

Also, `Type1` and `Type2` can be both of type

- `Line_2<Kernel>`
- `Circle_2<Kernel>`

In three-dimensional space, the types `Type1` and
`Type2` can be any of the following:

- `Plane_3<Kernel>`
- `Line_3<Kernel>`
- `Ray_3<Kernel>`
- `Segment_3<Kernel>`
- `Triangle_3<Kernel>`.
- `Bbox_3`.

Also, `Type1` and `Type2` can be respectively of types

- `Triangle_3<Kernel>` and `Tetrahedron_3<Kernel>`
- `Plane_3<Kernel>` and `Sphere_3<Kernel>` (or the contrary)
- `Sphere_3<Kernel>` and `Sphere_3<Kernel>`.

*/
bool do_intersect(Type1<Kernel> obj1, Type2<Kernel> obj2);
/// @}

/*!
\addtogroup intersection

\brief 
\details Depending on which \cgal kernel is used, different overloads of this global
function are available.

### Notes on Backward Compatibility ###

The `intersection()` function used to return an `Object`, but starting with 
\cgal 4.2 the
return type is determined by a metafunction defined by the kernel. To
preserve backward compatibility `Object` can be
constructed from the new return types implicitly, but switching to the
new style is recommended. To enable the old style without any overhead,
the macro `CGAL_INTERSECTION_VERSION` must be defined to
`1` before any \cgal header is included.

### Upgrading code from CGAL::Object to boost::variant###

Code can be upgraded by using either `boost::get` or the
`boost::static_visitor<T>`.

\code
#include <CGAL/intersections.h>

template<typename R>
struct Intersection_visitor : public boost::static_visitor<> {
  void operator()(const Point_2& p) const 
  { // Point_2  
  }
  void operator()(const Segment_2& s) const 
  { // Segment_2 
  }
};

template <class R>
void foo(Segment_2<R> seg, Line_2<R> lin)
{
  CGAL::Object obj = intersection(seg1, seg2);
  if(const Point_2* foo = object_cast<Point_2>(&obj)) {
    // Point_2 
  } else if(const Segment_2* foo = object_cast<Segment_2>(&obj)) {
    // Segment_2 
  } else {
    // empty
  }

  // becomes
  auto result = intersection(seg, lin);
  if(result) {
    if(const Point_2* foo = boost::get<Point_2>(&*obj)) {
      // Point_2 
    } else if(const Segment_2* foo = boost::get<Segment_2>(&*obj)) {
      // Segment_2 
    }
  } else {
    // empty
  }

  // or with boost::static_visitor<T>
  if(result) { boost::apply_visitor(Intersection_visitor(), *result); } 
  else { // empty  
  }
}
\endcode

*/


/*!
\addtogroup intersection_linear intersection (2D/3D Linear Kernel)
\ingroup intersection

\sa `do_intersect` 

*/
/// @{

/*!
Two objects `obj1` and `obj2` intersect if there is a point `p` that
is part of both `obj1` and `obj2`.  The intersection region of those
two objects is defined as the set of all points `p` that are part of
both `obj1` and `obj2`.  Note that for objects like triangles and
polygons that enclose a bounded region, this region is considered part
of the object.  If a segment lies completely inside a triangle, then
those two objects intersect and the intersection region is the
complete segment. 

Here, `Intersect_23` means either `Intersect_2` or `Intersect_3`,
depending on the arguments.

The possible values for types `Type1` and `Type2` and
the value for `T...` in `boost::optional< boost::variant<
  T... > >` are the following and can be obtained through
`boost::result_of(Intersect_2(A, B)>::type` or
`boost::result_of(Intersect_3(A, B)>::type`.
 


<DIV ALIGN="CENTER">
<TABLE CELLPADDING=3 BORDER="1">
<TR> <TH> Type1 </TH>
 <TH> Type2 </TH>
 <TH> Return Type:  `T...` </TH>
</TR>
<TR>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD>Iso_rectangle_2</TD>
</TR>

<TR>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Iso_rectangle_2 </TD>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD>Point_2, or Segment_2, or Triangle_2, or std::vector&lt;Point_2&gt;</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD>Point_2, or Line_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD>Point_2, or Ray_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_2 </TD>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD>Point_2, or Segment_2, or Ray_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_2 </TD>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Segment_2 </TD>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD>Point_2, or Segment_2</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD VALIGN="CENTER" > Triangle_2 </TD>
    <TD>Point_2, or Segment_2, or Triangle_2, or std::vector&lt;Point_2&gt;</TD>
</TR>

</TABLE>
<TABLE CELLPADDING=3 BORDER="1">
<TR> <TH> Type1 </TH>
 <TH> Type2 </TH>
 <TH> Return Type: `T...` </TH>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD>Point_3, or Line_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD>Point_3, or Line_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD>Point_3, or Ray_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Line_3 </TD>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD>Line_3, or Plane_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD>Point_3, or Ray_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD VALIGN="CENTER" > Sphere_3 </TD>
    <TD>Point_3, or Circle_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Plane_3 </TD>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
    <TD>Point_3, or Segment_3, or Triangle_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD>Point_3, or Ray_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Ray_3 </TD>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
p    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Segment_3 </TD>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
    <TD>Point_3, or Segment_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Sphere_3 </TD>
    <TD VALIGN="CENTER" > Sphere_3 </TD>
    <TD>Point_3, or Circle_3, or Sphere_3</TD>
</TR>
<TR>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
    <TD VALIGN="CENTER" > Triangle_3 </TD>
    <TD>Point_3, or Segment_3, or Triangle_3, or std::vector &lt; Point_3  &gt;</TD>
</TR>
</TABLE>
</DIV>

### Example ###

The following example demonstrates the most common use of 
`intersection` routines with the 2D and 3D Linear %Kernel.

\code
#include <CGAL/intersections.h>

template<typename R>
struct Intersection_visitor {
  typedef result_type void;
  void operator()(const Point_2<R>& p) const 
  { // handle point
  }
  void operator()(const Segment_2<R>& s) const 
  { 
    // handle segment 
  }
};

template <class R>
void foo(const Segment_2<R>& seg, const Line_2<R>& lin)
{
  // with C++11 support
  // auto result = intersection(seg, lin);

  // without C++11
  boost::result_of<R::Intersect_2(Segment_2<R>, Line_2<R>)>::type 
    result = intersection(seg, lin);

  if(result) { boost::apply_visitor(Intersection_visitor(), *result); } 
  else { 
    // no intersection 
  }

  // alternatively:
  if(result) {
    if(const Segment_2<R>* s = boost::get<Segment_2>(&*result)) {
      // handle segment
    } else {
      const Point_2<R>* p = boost::get<Point_2>(&*result);
      // handle point
    }
}
\endcode


Another example showing the use of the intersection function as a plain function call and with `Dispatch_output_iterator` combined with a standard library algorithm.

\cgalExample{Kernel_23/intersections.cpp}



*/
boost::result_of<Intersect_23(Type1, Type2)>::type
intersection(Type1<Kernel> obj1, Type2<Kernel> obj2);

/*!
returns the intersection of 3 planes, which can be either a
point, a line, a plane, or empty.
*/
boost::optional< boost::variant< Point_3, Line_3, Plane_3 > > 
intersection(const Plane_3<Kernel>& pl1,
             const Plane_3<Kernel>& pl2,
             const Plane_3<Kernel>& pl3);

/// @}
}
