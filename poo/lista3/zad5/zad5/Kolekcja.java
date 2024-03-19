import java.util.Collection;
import java.util.Iterator;

public class ExampleClass implements Collection {
	// TO MOZE ZOSTAC
    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }
    
	// TO MOZE ZOSTAC
    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

	// TO MOZE ZOSTAC
    @Override
    public boolean add(Object o) {
        return false;
    }
	// TO MOZE ZOSTAC
    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean addAll(Collection c) {
        return false;
    }
	
	// TO MOZE ZOSTAC
    @Override
    public void clear() {

    }

    @Override
    public boolean retainAll(Collection c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection c) {
        return false;
    }

    @Override
    public boolean containsAll(Collection c) {
        return false;
    }

    @Override
    public Object[] toArray(Object[] a) {
        return new Object[0];
    }
}
