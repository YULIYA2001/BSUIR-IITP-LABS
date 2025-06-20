package sample.classes.iterator;

import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;

// Паттерн Iterator (возможность последовательно обходить элементы составных объектов,
// не раскрывая их внутреннего представления)

// Итератор читает json строку из файла, переводит ее в указанный класс Class<T> и возвращает объект класса
public class TextFileReader<T> implements Container {

    final Class<T> typeParameterClass;
    // Полный путь
    private final String fileName;

    public TextFileReader(final String fileName, Class<T> typeParameterClass) {
        this.fileName = fileName;
        if (fileName == null){
            System.out.println("WRONG IN TextFileReader EMPTY PATH TO FILE");
            System.exit(0);
        }
        this.typeParameterClass = typeParameterClass;
    }

    public MyIterator getIterator(){
        return new TextFileIterator();
    }

    private final class TextFileIterator implements MyIterator {

        final BufferedReader in;

        String nextline;

        public TextFileIterator() {
            try {
                in = new BufferedReader(new FileReader(fileName));
                nextline = in.readLine();
            } catch (IOException e) {
                throw new IllegalArgumentException(e);
            }
        }

        @Override
        public boolean hasNext() {
            return nextline != null;
        }

        @Override
        public Object next() {
            Object res;
            try {
                String result = nextline;
                if (nextline != null) {
                    nextline = in.readLine();
                    if (nextline == null) {
                        in.close();
                    }
                }
                res = sample.classes.MyJSON.fromJSON(result, typeParameterClass);
            } catch (IOException e) {
                throw new IllegalArgumentException(e);
            }
            return res;
        }
    }
}