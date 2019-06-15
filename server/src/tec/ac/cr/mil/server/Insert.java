package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.DatabaseFacade;
import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;
import java.io.IOException;

@Path("insert")
public class Insert {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public void addPicture(Picture picture) throws IOException {
        System.out.println(2);
        DatabaseFacade.INSERT(picture);
    }

}
