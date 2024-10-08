//
// Created by 王晨辉 on 2024/2/1.
//

#include "DataArrayBase.h"


namespace DATA {
DataArrayBase::DataArrayBase(const std::string& name, const DisjointRanges& ranges)
    : name(name)
    , ranges(ranges) {}

DataArrayBase::~DataArrayBase() {}

int DataArrayBase::ValueId(int entryId, const DisjointRanges& disjointRanges) {
    int ret = 0;
    for (const auto& range : disjointRanges) {
        if (entryId < range.upper) {
            if (entryId >= range.lower) {
                ret += (entryId - range.lower);
                return ret;
            } else {
                return -1;
            }
        } else {
            ret += (range.upper - range.lower);
        }
    }
    return -1;
}

int DataArrayBase::ValueId(int entryId) const {
    return DataArrayBase::ValueId(entryId, ranges);
}
}   // namespace DATA