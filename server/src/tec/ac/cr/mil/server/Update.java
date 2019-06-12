package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;

@Path("update")
public class Update {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public void updatePicture(Picture picture){
        System.out.println(3);
        //Aqui va para agregar la foto
    }

}
