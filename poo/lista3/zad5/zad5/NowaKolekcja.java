import java.util.Iterator;

interface Sizeable {
    int size();
    boolean isEmpty();
}


interface Modifiable {
    boolean add(Object o);
    boolean remove(Object o);
    boolean addAll(Collection c);
    void clear();
    boolean retainAll(Collection c);
    boolean removeAll(Collection c);
}


interface Queryable {
    boolean contains(Object o);
    boolean containsAll(Collection c);
}


interface Iterable {
    Iterator iterator();
}


public class ExampleClass implements Sizeable, Modifiable, Queryable, Iterable {
    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator iterator() {
        return null;
    }

    @Override
    public boolean add(Object o) {
        return false;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean addAll(Collection c) {
        return false;
    }

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
}
