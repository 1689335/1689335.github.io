#pragma once

#include <cstdint>
#include <iostream>
using namespace std;

template<typename T, uint32_t BlockSize = 1024>
class ObjectPool 
{
public:
    ObjectPool() noexcept = default;                     // 构造函数
    ObjectPool(const ObjectPool &pool) noexcept = delete; // 拷贝构造函数
    ObjectPool &operator=(const ObjectPool &pool) = delete;

    ObjectPool(ObjectPool &&pool) noexcept = delete;      // 移动构造函数
    ObjectPool &operator=(ObjectPool &&pool) noexcept = delete;
 
    ~ObjectPool() noexcept {
        Node *block = blocks;
        while (block != nullptr) {
            Node *nextBlock = block->next;
            ::operator delete(reinterpret_cast<void *>(block));
            block = nextBlock;
        }   
    }

    

    void Dump() noexcept {
        Node *block = blocks;
        while (block != nullptr) {
            cout << "block" << (uint64_t)block << endl;
            Node *nextBlock = block->next;
            //DumpBlock(nextBlock);
        
            block = nextBlock;
        }

        cout << "FreeList";
        block = frees;
        while (block != nullptr) {
            cout << "    block" << (uint64_t)block << endl;
          block = block->next;
        }
    }

    // void DumpBlock(Node *block) {
    //     while (block != nullptr) {
    //         cout << "    block" << (uint64_t)block << endl;
    //         block = block->next;
    //     }
    // }

    inline T *Alloc() {
        if (frees != nullptr) {
            T *obj = reinterpret_cast<T *>(frees);
            frees = frees->next;
            return obj;
        }
        
        return AllocBlock();
    }


    T *AllocBlock() {

        Node *newBlock = reinterpret_cast<Node *>(::operator new(BlockSize * sizeof(Node)));
        newBlock->next = blocks;
        blocks = newBlock;
    
        newBlock->next = frees;
        auto pre = newBlock++;
    
        for (int i = 1 ;i < BlockSize; ++i, ++newBlock) {
            newBlock->next = pre;
            pre = newBlock;
        }

        frees = newBlock;

        Node *n = frees;
        frees = frees->next;

        return reinterpret_cast<T *>(n);
    }

  inline void Free(void *p) {
    if (p != nullptr) {
        auto slots = reinterpret_cast<Node *>(p);
        slots->next = frees;
        frees = slots;
    }
  }

 private:
  union Node {
    T data;
    Node *next;
  };

  Node *blocks{nullptr};
  Node *frees{nullptr};
};









#if 0
  template <typename U, typename... Args>
  inline void construct(U *p, Args &&... args) {
    new (p) U(std::forward<Args>(args)...);
  }
  template <typename U> inline void destroy(U *p) { p->~U(); }

  /**************
  * new与delete *
  **************/
  template <typename... Args> inline T *newElement(Args &&... args) {
    T *result = allocate();
    construct(result, std::forward<Args>(args)...);
    return result;
  }
  inline void deleteElement(T *p) {
    if (p != nullptr) {
      p->~T();
      deallocate(p);
    }
  }

  /********************
  * 最多能容纳多少个对象 *
  ********************/
  inline size_t max_size() const noexcept {
    // -1 表示当前能寻址的最大内存地址
    // -1 / BlockSize 就可以得出最大 Block 数
    size_t maxBlocks = -1 / BlockSize;
    // 每个 Block 能容纳的 T 的个数 乘 最大 Block 数
    return (BlockSize - sizeof(char *)) / sizeof(Node) * maxBlocks;
  }
#endif

