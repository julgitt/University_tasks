using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wektory
{
    public class Wektor
    {
        protected int dimensions;
        protected float[] coordinates;

        public Wektor(int dim, float[] coords)
        {
            this.dimensions = dim;
            this.coordinates = new float[dim];
            if (coords.Length != dim)
            {
                throw new ArgumentException();
            }

            coordinates = coords;
        }

        public static Wektor operator +(Wektor v1, Wektor v2)
        {
            if (v1.dimensions != v2.dimensions)
            {
                throw new ArgumentException();
            }

            int dim = v1.dimensions;
            float[] coords = new float[dim];
            for (int i = 0; i < dim; i++)
            {
                coords[i] = v1.coordinates[i] + v2.coordinates[i];
            }
            return new Wektor(dim, coords);
        }

        public static float operator *(Wektor v1, Wektor v2)
        {
            if (v1.dimensions != v2.dimensions)
            {
                throw new ArgumentException();
            }

            int dim = v1.dimensions;
            float result = 0;
            for (int i = 0; i < dim; i++)
            {
                result += v1.coordinates[i] * v2.coordinates[i];
            }
            return result;
        }

        public static Wektor operator *(float number, Wektor v)
        {
            int dim = v.dimensions;
            float[] coords = new float[dim];
            for (int i = 0; i < dim; i++)
            {
                coords[i] += number * v.coordinates[i];
            }
            return new Wektor(dim, coords);
        }
        public float norma()
        {
            return (float)Math.Sqrt(this * this);
        }
    }

}
