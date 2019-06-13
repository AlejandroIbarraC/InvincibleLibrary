package tec.ac.cr.mil.logic;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.FileAlreadyExistsException;
import java.util.List;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

public class Serializer {

    public static void serialize(){
        ObjectMapper mapper = new ObjectMapper();
        try {
            mapper.writeValue(new File("../MyInvincibleLibrary/server/src/tec/ac/cr/mil/logic/PictureData.json"), pictureArrayList);
            String jsonInString = mapper.writeValueAsString(pictureArrayList);
            System.out.println(jsonInString);
        }catch (JsonGenerationException e) {
            //e.printStackTrace();
        }catch (JsonMappingException e) {
            //e.printStackTrace();
        }catch (IOException e) {
           // e.printStackTrace();
        }
    }

    public static void deserialize() {
        ObjectMapper mapper = new ObjectMapper();
        try{
            pictureArrayList = mapper.readValue(new File("../MyInvincibleLibrary/server/src/tec/ac/cr/mil/logic/PictureData.json"), new TypeReference<List<Picture>>(){});
        } catch (JsonGenerationException e) {
            //e.printStackTrace();
        } catch (JsonMappingException e) {
            //e.printStackTrace();
        } catch (IOException e) {
           // e.printStackTrace();
        }

    }
}

