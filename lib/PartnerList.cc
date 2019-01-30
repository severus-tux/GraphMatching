#include "PartnerList.h"
#include "Vertex.h"
#include <algorithm>
#include <sstream>

PartnerList::~PartnerList() {
    partners_.clear();
}

bool PartnerList::empty() const {
    return partners_.empty();
}

PartnerList::SizeType PartnerList::size() const {
    return partners_.size();
}

PartnerList::ConstIterator PartnerList::cbegin() const {
    return partners_.cbegin();
}

PartnerList::ConstIterator PartnerList::cend() const {
    return partners_.cend();
}

PartnerList::Iterator PartnerList::begin() {
    return partners_.begin();
}

PartnerList::Iterator PartnerList::end() {
    return partners_.end();
}

PartnerList::ConstIterator PartnerList::find(VertexPtr v) const {
    for (auto i = cbegin(), e = cend(); i != e; ++i) {
        if (i->vertex == v) {
            return i;
        }
    }

    return cend();
}

/// add a vertex to the list of matched partners
void PartnerList::add_partner(VertexPtr partner, RankType rank, int level) {
    partners_.emplace_back(partner, rank, level);
}

/// return details for the worst partner matched to this vertex
PartnerList::ConstIterator PartnerList::find_least_preferred() const {
    if (empty()) {
        return cend();
    } else {
        auto min_it = cbegin();

        for (auto i = cbegin(), e = cend(); i != e; ++i) {
            if (*i < *min_it) {
                min_it = i;
            }
        }

        return min_it;
    }
}

Partner PartnerList::get_least_preferred() const {
    return *find_least_preferred();
}

void PartnerList::remove(VertexPtr v) {
    partners_.remove_if([v] (const Partner& p) { return p.vertex == v; });
}

/// remove the least preferred among the current partners
void PartnerList::remove_least_preferred() {
    auto it = find_least_preferred();

    if (it != end()) {
        partners_.erase(it);
    }
}
