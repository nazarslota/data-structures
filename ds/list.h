#ifndef DATA_STRUCTURES_LIST_H
#define DATA_STRUCTURES_LIST_H

#include <memory>

namespace ds {
    template<typename ValueType>
    class list {
        using value_type = ValueType;
        using size_type = std::size_t;

    public:
        class node {
            friend class list;

        public:
            explicit node(const value_type &value);

        private:
            node *get_next() { return p_next_.get(); }

            node *get_prev() { return p_prev_.get(); }

            const node *get_const_next() { return p_next_.get(); }

            const node *get_const_prev() { return p_prev_.get(); }

            std::shared_ptr<node> move_next() { return std::move(p_next_); }

            std::shared_ptr<node> move_prev() { return std::move(p_prev_); }

            void set_next(const value_type &value) { p_next_ = std::make_shared<node>(value); }

            void set_prev(const value_type &value) { p_prev_ = std::make_shared<node>(value); }

            void set_next(const std::shared_ptr<node> &node) { p_next_ = node; }

            void set_prev(const std::shared_ptr<node> &node) { p_prev_ = node; }

            void set_next(std::shared_ptr<node> &&node) { p_next_ = std::move(node); }

            void set_prev(std::shared_ptr<node> &&node) { p_prev_ = std::move(node); }

        private:
            value_type m_value_{value_type()};
            std::shared_ptr<node> p_next_{nullptr};
            std::shared_ptr<node> p_prev_{nullptr};
        };

    public:
        void push_back(const value_type &value);

        void push_front(const value_type &value);

    private:
        size_type m_size_{0};
        std::shared_ptr<node> p_head_{nullptr};
        std::shared_ptr<node> p_tail_{nullptr};
    };

    template<typename ValueType>
    list<ValueType>::node::node(const value_type &value) :
            m_value_(value) {
    }

    template<typename ValueType>
    void list<ValueType>::push_back(const value_type &value) {
        if (p_head_ == nullptr) {
            p_head_ = std::make_shared<node>(value);
            p_tail_ = p_head_;
            p_tail_->set_next(p_head_);
            return;
        }

        std::shared_ptr<node> temp = std::move(p_tail_);
        p_tail_ = std::make_shared<node>(value);
        temp->set_next(p_tail_);

        p_tail_->set_prev(std::move(temp));
    }

    template<typename ValueType>
    void list<ValueType>::push_front(const value_type &value) {
        std::shared_ptr<node> temp = std::move(p_head_);
        p_head_ = std::make_shared<node>(value);
        temp->set_prev(p_head_);

        p_head_->set_next(std::move(temp));
    }
} // ds

#endif // DATA_STRUCTURES_LIST_H
