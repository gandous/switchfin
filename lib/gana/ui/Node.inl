
template<typename T, typename ...ARGS>
T *Node::make_managed(ARGS&& ...args)
{
    std::shared_ptr<T> ptr = std::make_shared<T>(args...);
    _managed_childs.push_back(ptr);
    return (ptr.get());
}