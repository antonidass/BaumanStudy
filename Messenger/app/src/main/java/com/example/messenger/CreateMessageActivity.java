ffffffffpackage com.example.messenger;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class CreateMessageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_mesage);
    }

    public void onSendMessage(View view) {
        EditText text = (EditText) findViewById(R.id.message);
        String messageText = text.getText().toString();

//        Intent intent = new Intent(this, ReceiveMessageActivity.class);
//        intent.putExtra("message", text.getText().toString());

        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setType("text/plain");
//        Intent intent1 = Intent.createChooser(intent, "lol");
//        intent.putExtra(Intent.EXTRA_SUBJECT, "theme of message");
        intent.putExtra(Intent.EXTRA_TEXT, messageText);

        String chooserTitle = getString(R.string.chooser);
        Intent chooserIntent = Intent.createChooser(intent, chooserTitle);
        startActivity(chooserIntent);

//        startActivity(intent);
    }
}