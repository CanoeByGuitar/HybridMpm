//
// Created by 王晨辉 on 2024/2/1.
//

#ifndef HYBRIDMPM_DATAARRAY_H
#define HYBRIDMPM_DATAARRAY_H

namespace DATA {
/**
    DataArray represents a continuous memory block of entry data.
    It has two members.
    1. ranges.
        This is an array of sorted ranges of global entry IDs,
        inclusive on the left, exclusive on the right.
        For example, [0,3), [6,8) means this batch stores data for entries
        0,1,2,6,7
    2. array.
        This is an array of data with any type. E.g., for positions.
        The array stores contiguous data for the entities in the ranges
        Continuing the example if the array is [1, 2, 3, 4, 5]
        then the entries and correspoding values are as follows
        |Entry |   ValueId |   Value |
        |  0   |     0     |     1   |
        |  1   |     1     |     2   |
        |  2   |     2     |     3   |
        |  3   |    NA     |    NA   |
        |  4   |    NA     |    NA   |
        |  5   |    NA     |    NA   |
        |  6   |     3     |     4   |
        |  7   |     4     |     5   |

*/

template<typename Type, bool is_const> class DataArrayIterator;









}   // namespace DATA

#endif   // HYBRIDMPM_DATAARRAY_H
