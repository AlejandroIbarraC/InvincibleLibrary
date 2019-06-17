package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.DatabaseFacade;
import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;

@Path("delete")
public class Delete {

    /**
     * Receives an image from the client to be deleted
     * @param picture that will be deleted
     */
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public void deletePicture(Picture picture){
        System.out.println(1);
        DatabaseFacade.DELETE(picture);
    }

}
