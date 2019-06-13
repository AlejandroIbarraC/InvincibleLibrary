package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.DatabaseFacace;
import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;

@Path("select")
public class Select {

    @GET
    @Path("all")
    @Produces(MediaType.APPLICATION_JSON)
    public ArrayList<Picture> getAllPictures(){
        System.out.println(5);
        return DatabaseFacace.SELECT();
    }

}
