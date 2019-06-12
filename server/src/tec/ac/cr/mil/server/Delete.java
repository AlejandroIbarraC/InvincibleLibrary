package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;

@Path("delete")
public class Delete {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public void deletePicture(Picture picture){
        System.out.println(1);
        //Aqui va para eliminar imagen
    }

}
