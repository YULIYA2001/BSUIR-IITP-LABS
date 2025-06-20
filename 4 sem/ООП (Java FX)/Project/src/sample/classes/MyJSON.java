package sample.classes;

import com.alibaba.fastjson.JSON;

// паттерн Фасад (структурный паттерн, предоставляет простой интерфейс к библиотеке)
public class MyJSON {

    public static String toJSON(Object obj){
        return JSON.toJSONString(obj);
    }

    public static <T> T fromJSON(String jsonString, Class<T> clazz){
        return JSON.parseObject(jsonString, clazz);
    }
}
