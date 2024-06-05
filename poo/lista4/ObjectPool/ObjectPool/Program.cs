using System.Security.AccessControl;
using System.Xml.Linq;

namespace Zad3
{
    public class Reusable
    {
        public void DoWork()
        {
            Console.WriteLine("DoWork jest robione\n");
        }
    }

    public class ReusableWrapper
    {
        private Reusable _reusable;
        bool _disposed;
        private static ObjectPool _objectPool = new ObjectPool(1);

        public ReusableWrapper()
        {
            _reusable = _objectPool.AcquireReusable();
            _disposed = false;
        }

        public void DoWork()
        {
            if (_disposed)
                throw new ArgumentException();
            _reusable.DoWork();
        }

        public void Release()
        {
            if (_disposed)
                throw new ArgumentException();
            _objectPool.ReleaseReusable(_reusable);
            _disposed = true;
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }

            ReusableWrapper other = (ReusableWrapper)obj;
            return _reusable.Equals(other._reusable);
        }
    }


    public class ObjectPool
    {
        private int _capacity;

        private List<Reusable> _ready = new List<Reusable>();
        private List<Reusable> _released = new List<Reusable>();

        public ObjectPool(int capacity)
        {
            if (capacity <= 0)
            {
                throw new ArgumentException();
            }

            this._capacity = capacity;
        }

        public Reusable AcquireReusable()
        {
            if (_released.Count == this._capacity) 
            {
                throw new ArgumentException();
            }
            if (_ready.Count == 0)
            {
                Reusable newReusable = new Reusable();
                _ready.Add(newReusable);
            }
            var reusable = _ready[0];
            _ready.Remove(reusable);
            _released.Add(reusable);

            return reusable;
        }

        public void ReleaseReusable(Reusable reusable)
        {
            if (!_released.Contains(reusable))
            {
                throw new ArgumentException();
            }
            _released.Remove(reusable);
            _ready.Add(reusable);
        }
    }

}