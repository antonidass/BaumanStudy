package mooc.vandy.java4android.gate.ui;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import mooc.vandy.java4android.gate.logic.ClassToTest;
import mooc.vandy.java4android.gate.logic.Logic;
import mooc.vandy.java4android.gate.logic.LogicInterface;
import mooc.vandy.java4android.gate.logic.R;

/**
 * Main UI of this app.
 */
public class MainActivity
        extends AppCompatActivity
        implements OutputInterface {
    /**
     * String for LOGGING
     */
    public final static String LOG_TAG =
            MainActivity.class.getCanonicalName();

    /**
     * Logic Instance.
     */
    private LogicInterface mLogic;

    /**
     * EditText that stores the output.
     */
    private TextView mOutput;

    /**
     * The Spinner (drop down selector) that you choose which
     * shape to use.
     */
    private Spinner mShapesSpinner;

    /**
     * This 'Adapts' the Array of CharSequence to make it useable by
     * the mShapesSpinner.
     */
    private ArrayAdapter<CharSequence> mAdapter;

    /**
     * Called when the activity is starting.
     * <p>
     * Similar to 'main' in C/C++/Standalone Java
     *
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // required
        super.onCreate(savedInstanceState);

        // Create a new 'Logic' instance.
        mLogic = new Logic(this);

        // setup the UI.
        initializeUI();
    }

    /**
     * This method sets up/gets reference to the UI components
     */
    private void initializeUI() {
        // Set the layout.
        setContentView(R.layout.activity_main);

        // Initialize the views.
        mOutput = findViewById(R.id.outputET);
        mShapesSpinner = findViewById(R.id.spinner);

        // Initialize the adapter.
        mAdapter = ArrayAdapter.createFromResource(this,
                R.array.shapes,
                android.R.layout.simple_spinner_item);
        mAdapter.setDropDownViewResource
                (android.R.layout.simple_spinner_dropdown_item);

        // Connect the adapter to the Spinner.
        mShapesSpinner.setAdapter(mAdapter);
    }

    /**
     * Called when Button is Pressed.
     *
     * @param buttonPress
     */
    public void buttonPressed(View buttonPress) {
        resetText();
        mLogic.process();
    }

    /**
     * Set the EditText's text.
     */
    private void addToEditText(String string) {
        mOutput.setText("" + mOutput.getText() + string);
    }

    /**
     * Return the enumeration literal for the class to test.
     */
    public ClassToTest getClassToTest() {
        // valueOf(String) is an automatically generated method of all
        // Enum(s).  It returns an instance of the enum if one matches
        // the string provided.
        return ClassToTest.valueOf(mShapesSpinner.getSelectedItem().toString());
    }

    /**
     * Reset the on-screen output (EditText box).
     */
    @Override
    public void resetText() {
        mOutput.setText("");
    }

    /**
     * Prints the string representation of the passed Java Object or primitive type.
     *
     * @param obj a String, int, double, float, boolean or any Java Object.
     */
    @Override
    public void print(Object obj) {
        String text = (obj != null ? obj.toString() : "null");
        addToEditText(text);
        String debug = text.replace("\n", "\\n");
        Log.d(LOG_TAG, "print(" + debug + ")");
    }
}
