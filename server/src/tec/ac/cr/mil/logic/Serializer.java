package tec.ac.cr.mil.logic;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

public class Serializer {

    public static void main(String[] args) {

        Picture picture1 = new Picture("Hola", "kevin", 1298, 100, "dasdasd");
        Picture picture2 = new Picture("Sos", "chsas", 9999, 122, "grea");
        pictureArrayList.add(picture1);
        pictureArrayList.add(picture2);

        deserializer();
    }

    public static void serializer(){
        ObjectMapper mapper = new ObjectMapper();

        //For testing

        try {
            //Convert object to JSON string and save into file directly
            mapper.writeValue(new File("D:\\shuzz.json"), pictureArrayList);

            //Convert object to JSON string
            String jsonInString = mapper.writeValueAsString(pictureArrayList);
            System.out.println(jsonInString);

            //Convert object to JSON string and pretty print
            jsonInString = mapper.writerWithDefaultPrettyPrinter().writeValueAsString(pictureArrayList);
            System.out.println(jsonInString);


        } catch (JsonGenerationException e) {
            e.printStackTrace();
        } catch (JsonMappingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void deserializer() {
        ObjectMapper mapper = new ObjectMapper();

        try {

            // Convert JSON string from file to Object
            Picture picture = mapper.readValue(new File("D:\\shuzz.json"), Picture.class);
            System.out.println(picture);

            // Convert JSON string to Object
            String jsonInString = "{\"age\":19,\"messages\":[\"holi 1\",\"holi 2\"],\"holi\":\"holi\"}";
            Picture picture1 = mapper.readValue(jsonInString, Picture.class);
            System.out.println(picture1);

        } catch (JsonGenerationException e) {
            e.printStackTrace();
        } catch (JsonMappingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    }

