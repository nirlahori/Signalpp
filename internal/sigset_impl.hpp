#ifndef SIGSET_IMPL_H
#define SIGSET_IMPL_H

#include <csignal>
#include <initializer_list>
#include <algorithm>

class SigSet
{

    using signal_type = int;
    using signal_set_type = sigset_t;
    signal_set_type signal_set;

    void add_signal_to_set(signal_type signal){
        sigaddset(&signal_set, signal);
    }

    void remove_signal_from_set(signal_type signal){
        sigdelset(&signal_set, signal);
    }

    void remove_all_signals_from_set(){
        sigemptyset(&signal_set);
    }

    void add_all_signals_to_set(){
        sigfillset(&signal_set);
    }

    bool is_signal_set_empty() const{
        return sigisemptyset(&signal_set);
    }

    bool is_signal_in_set(signal_type signal) const{
        return sigismember(&signal_set, signal);
    }

    void copy_set(const signal_set_type* src, signal_set_type* dest){
        for(int sig{0}; sig<SIGRTMAX; sig++){
            if(sigismember(src, sig)){
                sigaddset(dest, sig);
            }
        }
    }

    void move_set(signal_set_type* src, signal_set_type* dest){
        for(int sig{0}; sig<SIGRTMAX; sig++){
            if(sigismember(src, sig)){
                sigaddset(dest, sig);
                sigdelset(src, sig);
            }
        }
    }

    void init_set(){
        remove_all_signals_from_set();
    }

public:

    SigSet() {
        init_set();
    }

    SigSet(const std::initializer_list<int>& signal_list){
        init_set();
        auto add_signal_to_set = [this](const int& signal){sigaddset(&signal_set, signal);};
        std::for_each(signal_list.begin(), signal_list.end(), add_signal_to_set);
    }

    SigSet(const signal_set_type* srcset){
        copy_set(srcset, &signal_set);
    }


    SigSet(const SigSet& other){
        copy_set(other.get_native_handle(), &signal_set);
    }

    SigSet& operator= (const SigSet& other){
        copy_set(&other.signal_set, &signal_set);
        return *this;
    }

    SigSet(SigSet&& other){
        move_set(&other.signal_set, &signal_set);
    }
    SigSet& operator= (SigSet&& other){
        move_set(&other.signal_set, &signal_set);
        return *this;
    }

    void insert_signal(const signal_type& signal){
        add_signal_to_set(signal);
    }

    void delete_signal(const signal_type& signal){
        remove_signal_from_set(signal);
    }

    void replace_set(const std::initializer_list<signal_type>& signal_list){
        remove_all_signals_from_set();
        auto add_signal_to_set = [this](const int& signal){sigaddset(&signal_set, signal);};
        std::for_each(signal_list.begin(), signal_list.end(), add_signal_to_set);
    }

    void fill_set(){
        add_all_signals_to_set();
    }

    void clear(){
        remove_all_signals_from_set();
    }

    bool is_in_set(const signal_type& signal) const{
        return is_signal_in_set(signal);
    }

    bool empty() const{
        return is_signal_set_empty();
    }

    const signal_set_type* get_native_handle() const{
        return &signal_set;
    }

};

#endif // SIGSET_IMPL_H
