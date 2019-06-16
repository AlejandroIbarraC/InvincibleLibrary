package tec.ac.cr.mil.ml;

import org.tensorflow.Graph;
import org.tensorflow.Session;
import org.tensorflow.Tensor;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

public class ObjectRecognizer {

    private ObjectRecognizer(){}

    public static ObjectRecognizer getInstance(){
        if (objectRecognizer == null){
            objectRecognizer = new ObjectRecognizer();
        }
        return objectRecognizer;
    }

    private static ObjectRecognizer objectRecognizer = null;

    byte[] graphDef;
    String imagepath;
    List<String> labels;
    String modelpath;

    private static float[] executeInceptionGraph(byte[] graphDef, Tensor image) {
        try (Graph graph = new Graph()) {
            graph.importGraphDef(graphDef);
            try (Session s = new Session(graph);
                 Tensor result = s.runner().feed("DecodeJpeg/contents", image).fetch("softmax").run().get(0)) {
                final long[] rshape = result.shape();
                if (result.numDimensions() != 2 || rshape[0] != 1) {
                    throw new RuntimeException(
                            String.format(
                                    "Expected model to produce a [1 N] shaped tensor where N is the number of labels, instead it produced one with shape %s",
                                    Arrays.toString(rshape)));
                }
                int nlabels = (int) rshape[1];
                float[][] resultArray = new float[1][nlabels];
                result.copyTo(resultArray);
                return resultArray[0];
            }
        }
    }

    private static int maxIndex(float[] probabilities) {
        int best = 0;
        for (int i = 1; i < probabilities.length; ++i) {
            if (probabilities[i] > probabilities[best]) {
                best = i;
            }
        }
        return best;
    }

    private static byte[] readBytes(Path path) {
        try {
            return Files.readAllBytes(path);
        } catch (IOException e) {
            System.err.println("Failed to read [" + path + "]: " + e.getMessage());
            System.exit(1);
        }
        return null;
    }

    private static List<String> readLines(Path path) {
        try {
            return Files.readAllLines(path, Charset.forName("UTF-8"));
        } catch (IOException e) {
            System.err.println("Failed to read [" + path + "]: " + e.getMessage());
            System.exit(0);
        }
        return null;
    }

    public String getDescription(byte[] imageBytes) {
        // Define ML model
        File file = new File("C:\\Users\\Kevin Cordero Zúñiga\\IdeaProjects\\MyInvincibleLibrary\\server\\src\\tec\\ac\\cr\\mil\\ml\\model");
        modelpath = file.getAbsolutePath();
        graphDef = ObjectRecognizer.readBytes(Paths.get(modelpath,"tensorflow_inception_graph.pb"));
        labels = ObjectRecognizer.readLines(Paths.get(modelpath, "imagenet_comp_graph_label_strings.txt"));

        try (Tensor image = Tensor.create(imageBytes)) {
            float[] labelProbabilities = ObjectRecognizer.executeInceptionGraph(graphDef, image);
            int bestLabelIdx = ObjectRecognizer.maxIndex(labelProbabilities);

            return labels.get(bestLabelIdx);
        }
    }

}
