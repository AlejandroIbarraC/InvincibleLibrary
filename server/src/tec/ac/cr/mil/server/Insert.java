package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;

@Path("insert")
public class Insert {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public void addPicture(Picture picture){
        System.out.println(2);
        //Aqui va para agregar imagen
    }

}
