/* 4. 
Czym różni się mechanizm finalizerów (zwanych dawniej destruktorami)
od mechanizmu uwalniania zasobów za pomocą implementacji interfejsu IDisposable?

Jeden jest deterministyczny (mozemy sami zdecydować kiedy wyoluje sie metoda sprzatajaca zasoby), drugi nie.

Zaprezentować oba w praktyce: przygotować klasę która ma finalizer i inną klasę implementującą interfejs IDisposable.
W obu podejściach wywołać Console.WriteLine z metody sprzątającej.

Zaprezentować lukier syntaktyczny opakowujący użycie obiektu implementującego IDisposable
w blok ze słowem kluczowym using.

Zaobserwować, że w przypadku interfejsu IDisposable programista ma pełną kontrolę
nad momentem w którym wykonuje się metoda Dispose.
Zaobserwować że programista nie ma wpływu na to kiedy wykona się finalizer klasy.
Czy można wymusić wywołanie metody sprzątającej pamięć (odśmiecacz)? Czy to dobry
pomysł, żeby wymuszać to we własnym kodzie?
*/

using System;
using System.ComponentModel;
using System.Reflection.Metadata;

namespace Task4_List2
{
    public class Finalizer_Class
    {
        int a, b;
        public Finalizer_Class(int a, int b)
        {
            this.a = a;
            this.b = b;
        }
        ~Finalizer_Class()
        {
            Console.WriteLine("Calling finalizer from Finalizer_Class");
        }
    }
    public class IDisposable_Class :IDisposable
    {
        // Pointer to an external unmanaged resource.
        private IntPtr handle;
        // Other managed resource this class uses.
        private Component component = new Component();

        private bool disposed = false;
        public IDisposable_Class(IntPtr handle)
        {
            this.handle = handle;
        }
        
        public void SomeMethod()
        {
            Console.WriteLine("Calling SomeMethod in the using(){} syntax sugar");
        }

        public void Dispose()
        {
            Console.WriteLine("Calling Dispose() from IDisposable_Class");
            Dispose(disposing: true);
            // take this object off the finalization queue
            // and prevent finalization code for this object
            // from executing a second time.
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            Console.WriteLine("Calling Dispose(bool disposing) from IDisposable_Class");
            // Check to see if Dispose has already been called.
            if (!this.disposed)
            {
                if (disposing)
                {
                    // Dispose managed resources.
                    component.Dispose();
                }

                // clean up unmanaged resources here.
                CloseHandle(handle);
                handle = IntPtr.Zero;

                // Note disposing has been done.
                disposed = true;
            }
        }
        // Use interop to call the method necessary
        // to clean up the unmanaged resource.
        [System.Runtime.InteropServices.DllImport("Kernel32")]
        private extern static Boolean CloseHandle(IntPtr handle);

        
        // This finalizer will run only if the Dispose method
        // does not get called.
        ~IDisposable_Class()
        {
            // Calling Dispose(disposing: false) is optimal in terms of
            // readability and maintainability.
            Console.WriteLine("Calling finalizer from IDisposable_Class");
            Dispose(disposing: false);
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            IntPtr external_resource = new IntPtr();
            // finalizer jest czescia garbage collectora, to kiedy "posprzata" nieuzywane zasoby jest niedeterministyczne,
            // dzieje sie gdy brakuje pamieci
            Finalizer_Class? finalizer_obj = new Finalizer_Class(1, 2);
            finalizer_obj = null;
            // nie jest zalecane wymuszanie odsmiecania, bo to droga operacja,
            // a poza tym nie wiadomo do konca ktore zasoby odsmieci
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
            GC.WaitForPendingFinalizers();

            using (IDisposable_Class disposable_obj = new IDisposable_Class(external_resource))
            {
                disposable_obj.SomeMethod();
            }
            /*
            IDisposable_Class disposable_obj = null;
            try
            {
                disposable_obj = new IDisposable_Class();
                disposable_obj.SomeMthod();
            }
            finally
            {
                if(disposable_obj != null)
                {
                    ((IDisposable)disposable_obj).Dispose();
                }
            } 
            */
        }
    }

}
