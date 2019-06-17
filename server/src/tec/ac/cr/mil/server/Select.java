package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.DatabaseFacade;
import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.io.IOException;
import java.util.ArrayList;

@Path("select")
public class Select {

    /**
     * Gets all the images from the database and sends them to the client
     * @return an arrayList with all the images from the database
     * @throws IOException in case of an error
     */
    @GET
    @Path("all")
    @Produces(MediaType.APPLICATION_JSON)
    public ArrayList<Picture> getAllPictures() throws IOException {
        System.out.println(5);
        return DatabaseFacade.SELECT();
    }

}
