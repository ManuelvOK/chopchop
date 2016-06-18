#ifndef HOOD_H
#define HOOD_H value

#include <jobs.h>

/* get_neighbour:
 * get a randomly selected schedule from the neighbour of the given <schedule>
 * note: the contents of the given schedule aren't changed
 */
struct jsp get_neighbour(const struct jsp schedule);

#endif /* ifndef HOOD_H */
