using System;
using System.Collections;

namespace Task6List3
{
    public class BinaryTreeNode<T>
    {
        BinaryTreeNode<T> _leftChild;
        BinaryTreeNode<T> _rightChild;
        T _value;

        //getters
        public BinaryTreeNode<T> LeftChild => _leftChild;
        public BinaryTreeNode<T> RightChild => _rightChild;
        public T Value => _value;

        //setter
        public BinaryTreeNode(T value, BinaryTreeNode<T> leftChild = null, BinaryTreeNode<T> rightChild = null)
        {
            _value = value;
            _leftChild = leftChild;
            _rightChild = rightChild;
        }

        public IEnumerator GetEnumerator()
        {
            return GetEnumeratorDFS();
            //return GetEnumeratorBFS();
        }

        public IEnumerator GetEnumeratorBFS()
        {
            Queue<BinaryTreeNode<T>> queue = new Queue<BinaryTreeNode<T>>();
            queue.Enqueue(this);

            while (queue.Count > 0)
            {
                BinaryTreeNode<T> node = queue.Dequeue();
                yield return node.Value;

                if (node.LeftChild != null)
                {
                    queue.Enqueue(node.LeftChild);
                }

                if (node.RightChild != null)
                {
                    queue.Enqueue(node.RightChild);
                }
            }
        }

       
        public IEnumerator GetEnumeratorDFS()
        {
            Stack<BinaryTreeNode<T>> stack = new Stack<BinaryTreeNode<T>>();
            stack.Push(this);

            while (stack.Count > 0)
            {
                BinaryTreeNode<T> node = stack.Pop();
                yield return node.Value;

                if (node.RightChild != null)
                {
                    stack.Push(node.RightChild);
                }

                if (node.LeftChild != null)
                {
                    stack.Push(node.LeftChild);
                }
            }

        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            //          1
            //      2       3
            //    4   5   6   7


            BinaryTreeNode<int> leftLeft = new BinaryTreeNode<int>(4);
            BinaryTreeNode<int> leftRight = new BinaryTreeNode<int>(5);
            BinaryTreeNode<int> left = new BinaryTreeNode<int>(2, leftLeft, leftRight);

            BinaryTreeNode<int> rightLeft = new BinaryTreeNode<int>(6);
            BinaryTreeNode<int> rightRight = new BinaryTreeNode<int>(7);
            BinaryTreeNode<int> right = new BinaryTreeNode<int>(3, rightLeft, rightRight);

            BinaryTreeNode<int> root = new BinaryTreeNode<int>(1, left, right);

            foreach (var value in root)
            {
                Console.Write("{0},", value);
            }
        }
    }
}