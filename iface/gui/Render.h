#pragma once

#include "Adaptor.h"

#include <atomic>
#include <functional>
#include <future>
#include <memory>

namespace gui {

class Render
{
public:
    static Render& instance()
    {
        static Render sInstance;
        return sInstance;
    }

    [[nodiscard]] int preinit() { return adaptor::_lvPreinit(); }
    [[nodiscard]] int init() { return adaptor::_lvInit(); }
    void deinit() { adaptor::_lvDeinit(); }
    
    void loop() 
    { 
        mIsLooping = true;
        adaptor::_lvLoop();
    }

    void post(lv_obj_t* obj, std::function<void(lv_obj_t*)> task) 
    { 
        if (!mIsLooping) {
            task(obj);
            return;
        }

        postRaw([obj, taskCopy = std::move(task)]() 
        { 
            taskCopy(obj); 
        });
    }    

    template <typename T>
    void post(lv_obj_t* obj, T data, std::function<void(lv_obj_t*, T)> task) 
    { 
        if (!mIsLooping) {
            task(obj, data);
            return;
        }

        postRaw([obj, dataCopy = std::move(data), taskCopy = std::move(task)]() 
        { 
            taskCopy(obj, dataCopy); 
        });
    }    
 
    template <typename ReturnValue>
    ReturnValue exec(lv_obj_t* obj, std::function<ReturnValue(lv_obj_t*)> task)
    {
        if (!mIsLooping) {
            return task(obj);
        }

        return execRaw([obj, taskCopy = std::move(task)]() {
            return taskCopy(obj);
        });
    }

    template <typename ReturnValue, typename Arg>
    ReturnValue exec(lv_obj_t* obj, Arg data, std::function<ReturnValue(lv_obj_t*, Arg)> task)
    {
        if (!mIsLooping) {
            return task(obj, data);
        }

        return execRaw([obj, dataCopy = std::move(data), taskCopy = std::move(task)]() {
            return taskCopy(obj, dataCopy);
        });
    }

protected:
    void postRaw(std::function<void()> task)
    {
        adaptor::_lvAsyncCall(task);
    };

    template <typename ReturnValue>
    ReturnValue execRaw(std::function<ReturnValue()> task)
    {
        auto p = std::make_shared<std::promise<ReturnValue>>();
        auto future = p->get_future();

        postRaw([taskCopy = std::move(task), promise = std::move(p)]() {
            try {
                auto result = taskCopy();
                promise->set_value(std::move(result));
            } catch (...) {
                promise->set_exception(std::current_exception());
            }
        });
       
        return future.get();
    }

private:
    Render() = default;
    virtual ~Render() = default;

    Render(const Render&) = delete;
    Render& operator=(const Render&) = delete;
    Render(Render&&) = delete;
    Render& operator=(Render&&) = delete;

protected:
    std::atomic<bool> mIsLooping = false;
};

} // namespace gui