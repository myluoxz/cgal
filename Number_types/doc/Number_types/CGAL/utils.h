namespace CGAL {

/*!
\ingroup nt_util

Not all values of a type need to be valid. 
The function `is_valid` returns whether the argument is valid. 

\sa `CGAL::Is_valid` 

*/
template <typename T>
bool is_valid(const T& x);

} /* namespace CGAL */

namespace CGAL {

/*!
\ingroup nt_util

The function `max` returns the larger of two values. 

\sa `CGAL::Max`

*/
template <typename T>
T max(const T& x, const T& y);

} /* namespace CGAL */

namespace CGAL {

/*!
\ingroup nt_util

The function `min` returns the smaller of two values. 

\sa `CGAL::Min` 

*/
template <typename T>
T min(const T& x, const T& y);

} /* namespace CGAL */
