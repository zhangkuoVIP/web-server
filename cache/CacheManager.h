//
// Created by ubuntu on 17-3-1.
//

#ifndef WEB_SERVER_CACHEMANAGER_H
#define WEB_SERVER_CACHEMANAGER_H
#include <string>
#include <cstring>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <mutex>
#include <fstream>
class CacheManager {
public:
    static void init(std::string enableCache, std::string cacheSize);
    static char* getReadBuffer(std::string & fileName);
    static void unlockMutex();
    static bool getCacheIsOpen();
private:
    static bool cacheIsOpen;
    static unsigned long maxMemorySize;
    static unsigned long allocatedMemorySize;

    struct MemBlock {
        std::shared_ptr<char> mem;
        std::shared_ptr<MemBlock> pre, next;
        MemBlock() {}
        MemBlock(const MemBlock & rhs) {
            mem = rhs.mem;
            pre = rhs.pre;
            next = rhs.next;
        }
        MemBlock(MemBlock && rhs) {
            mem = std::move(rhs.mem);
            pre = std::move(rhs.pre);
            next = std::move(rhs.next);
        }
        MemBlock& operator = (const MemBlock & rhs) {
            mem = rhs.mem;
            pre = rhs.pre;
            next = rhs.next;
        }
        MemBlock& operator = (const MemBlock && rhs) {
            mem = std::move(rhs.mem);
            pre = std::move(rhs.pre);
            next = std::move(rhs.next);
        }
    };

    struct LinkedList {
        std::shared_ptr<MemBlock> head, tail;
        size_t length;
        LinkedList() {
            length = 0;
        }

        size_t size() {
            return length;
        }

        MemBlock back() {
            return *tail;
        }

        void pop_back() {
            erase(tail.get());
        }

        void erase(MemBlock *node) {
            --length;
            if(length == 0) {
                head.reset();
                tail.reset();
                return ;
            }
            node->pre->next = node->next;
            node->next->pre = node->pre;

        }

        void push_front(MemBlock mem) {
            ++length;
            if(length == 1) {
                head = std::make_shared<MemBlock>(mem);
                tail = head;
                head->pre = head;
                head->next = head;
                return ;
            }
            std::shared_ptr<MemBlock> ptr = std::make_shared<MemBlock>(mem);
            head->next->pre = ptr;
            ptr->next = head->next;
            head = ptr;
        }

    };

    /* 内存页面置换采用LRU算法 memList为指向页面内存的指针 */

    static std::unordered_map<std::string, MemBlock *> nameToPtr;
    static std::map<MemBlock *, std::string> ptrToName;
    static LinkedList memlist;
    static std::mutex mutex;

};


#endif //WEB_SERVER_CACHEMANAGER_H