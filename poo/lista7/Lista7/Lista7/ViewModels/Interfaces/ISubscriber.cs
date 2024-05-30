using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lista7.ViewModels.Interfaces
{
    public interface ISubscriber<T>
    {
        void Handle(T notification);
    }
}
