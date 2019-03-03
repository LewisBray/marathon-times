// Container class to mimic std::map but the entries are ordered by
// the values and not the keys.  I've made the interface conform to
// the standard but I've only really implemented the things I need
// for this project.  An idea for the future would be to make this
// its own project, complete the interface, add unit tests, support
// custom allocators, etc...

#ifndef __VALUE_ORDERED_MAP_HPP__
#define __VALUE_ORDERED_MAP_HPP__

#include <functional>
#include <algorithm>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Compare = std::less<Value>>
class value_ordered_map
{
public:
    using value_type = typename std::pair<Key, Value>;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    bool empty() const noexcept { return map_.empty(); }
    size_t size() const noexcept { return map_.size(); }

    iterator begin() noexcept { return map_.begin(); }
    iterator end() noexcept { return map_.end(); }

    const_iterator begin() const noexcept { return map_.begin(); }
    const_iterator end() const noexcept { return map_.end(); }

    iterator find(const Key& key)
    {
        return std::find_if(map_.begin(), map_.end(),
            [&key](const value_type& value) { return (value.first == key); });
    }

    const_iterator find(const Key& key) const
    {
        return std::find_if(map_.begin(), map_.end(),   // Repeated code...
            [&key](const value_type& value) { return (value.first == key); });
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        if (map_.empty())
        {
            map_.push_back(value);
            return std::make_pair(this->begin(), true);
        }

        const iterator position = this->find(value.first);
        const bool alreadyInMap = (position != this->end());
        if (alreadyInMap)
            return std::make_pair(position, false);

        for (iterator it = this->begin(), end = this->end(); it != end; ++it)
        {
            if (value_less_(value.second, it->second))
            {
                map_.insert(it, value);
                return std::make_pair(it, true);
            }
        }

        map_.emplace_back(value);
        return std::make_pair(this->end() - 1, true);
    }

    iterator erase(const_iterator position)
    {
        return map_.erase(position);
    }

    void sort()
    {
        const auto pair_less = [this](const value_type& lhs, const value_type& rhs)
        {
            return value_less_(lhs.second, rhs.second);
        };

        std::sort(map_.begin(), map_.end(), pair_less);
    }

private:
    Compare value_less_;
    std::vector<value_type> map_;
};

#endif
