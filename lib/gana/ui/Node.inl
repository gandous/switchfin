
template<typename T>
T *Node::make_managed()
{
    std::shared_ptr<T> ptr = std::make_shared<T>();
    _managed_childs.push_back(ptr);
    return (ptr.get());
}