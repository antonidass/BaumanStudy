package vandy.mooc.aad2.assignment;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface Rubric {
    String value();

    double points();

    String goal();

    String reference();
}
