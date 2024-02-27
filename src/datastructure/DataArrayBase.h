//
// Created by 王晨辉 on 2024/2/1.
//

#ifndef HYBRIDMPM_DATAARRAYBASE_H
#define HYBRIDMPM_DATAARRAYBASE_H

#include "DisjointRanges.h"

namespace DATA {
/**
    The base class of DataArray. Stores the range vector.
*/
class DataArrayBase {
public:
    std::string name;
    DisjointRanges ranges;

    DataArrayBase(const std::string& name, const DisjointRanges& ranges);

    virtual ~DataArrayBase();

    virtual void Clear() = 0;
    virtual size_t Size() const = 0;

    static int ValueId(int entryId, const DisjointRanges& disjointRanges);
    int ValueId(int entryId) const;

};
}
#endif   // HYBRIDMPM_DATAARRAYBASE_H
