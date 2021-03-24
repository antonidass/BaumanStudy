import com.github.sh0nk.matplotlib4j.NumpyUtils;
import com.github.sh0nk.matplotlib4j.Plot;
import com.github.sh0nk.matplotlib4j.PythonConfig;
import com.github.sh0nk.matplotlib4j.PythonExecutionException;
import com.github.sh0nk.matplotlib4j.builder.ContourBuilder;
import com.github.sh0nk.matplotlib4j.builder.HistBuilder;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class GUI {

    public static void main(String[] args) throws PythonExecutionException, IOException {

        Plot plt = Plot.create(PythonConfig.pythonBinPathConfig("/usr/bin/python3"));
//
//        plt.plot()
//                .add(Arrays.asList(1.3, 2))
//                .label("label")
//                .linestyle("--");
//        plt.xlabel("xlabel");
//        plt.ylabel("ylabel");
//        plt.text(0.5, 0.2, "text");
//        plt.title("Title!");
//        plt.legend();
//        plt.show();


        Random rand = new Random();
        List<Double> x = IntStream.range(0, 1000).mapToObj(i -> rand.nextGaussian())
                .collect(Collectors.toList());

//        Plot plt = Plot.create();
        plt.hist().add(x).orientation(HistBuilder.Orientation.horizontal);
        plt.text(-10, 3, "Bu");



        plt.ylim(-5, 5);
        plt.legend();

        plt.title("histogram");
        plt.savefig("/tmp/histogram.png").dpi(200);
        plt.show();
// Don't miss this line to output the file!

    }
}
