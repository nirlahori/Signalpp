#ifndef SIGNAL_SERVICE_HPP
#define SIGNAL_SERVICE_HPP


#include <cstdio>
#include <csignal>
#include <initializer_list>

#include "internal/sigset_impl.hpp"



class Signal_Service
{

    using signal_type = int;

    const static auto max_signals {64};
    SigSet service_set;

public:
    Signal_Service() :
        service_set{}
    {}


    Signal_Service(const std::initializer_list<signal_type>& siglist) :
        service_set {siglist}
    {}


    void add_signal(const signal_type& signal){
        service_set.insert_signal(signal);
    }

    void remove_signal(const signal_type& signal){
        service_set.delete_signal(signal);
    }

    void set_mask(const std::initializer_list<signal_type>& signal_list){
        service_set.replace_set(signal_list);
    }


    bool check_signal(const signal_type& signal) const{
        return service_set.is_in_set(signal);
    }

    void clear_mask(){
        service_set.clear();
    }

    void fill(){
        service_set.fill_set();
    }
};

#endif // SIGNAL_SERVICE_HPP
