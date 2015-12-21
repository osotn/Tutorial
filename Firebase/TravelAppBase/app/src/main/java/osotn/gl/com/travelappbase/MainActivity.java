package osotn.gl.com.travelappbase;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.firebase.client.DataSnapshot;
import com.firebase.client.Firebase;
import com.firebase.client.FirebaseError;
import com.firebase.client.ValueEventListener;


public class MainActivity extends Activity {

    private static final String TAG = "TravelAppBase";

    private Firebase mFirebaseRef;

    private Button btnUpdate;
    private TextView textPoints, textDebug;
    private EditText editNumber, editDescription;

    private String[] sPoints = new String[10];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Firebase.setAndroidContext(this);

        // Setup our Firebase mFirebaseRef
        TextView textFirebaseURL = (TextView) findViewById(R.id.firebaseURL);
        mFirebaseRef = new Firebase(textFirebaseURL.getText().toString()).child("points");

        mFirebaseRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Log.d(TAG, "Firebase - onDataChange()");
                sPoints = dataSnapshot.getValue(String[].class);
                update();
            }

            @Override
            public void onCancelled(FirebaseError firebaseError) {

            }
        });


        btnUpdate = (Button) findViewById(R.id.update);
        textPoints = (TextView) findViewById(R.id.points);
        textDebug = (TextView) findViewById(R.id.debug);
        editNumber = (EditText) findViewById(R.id.editNumber);
        editDescription = (EditText) findViewById(R.id.editDescription);


        btnUpdate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {

                Log.d(TAG, "btnUpdate onClick()");
                //
                int n = -1;
                try {
                    n = Integer.parseInt(editNumber.getText().toString());
                } catch (Exception e) {
                    Log.d(TAG, "btnUpdate onClick() Exception " + e.toString());
                }

                int size = sPoints.length;
                if (n >= 0 && n < size) {
                    String text = editDescription.getText().toString();
                    Log.d(TAG, "btnUpdate onClick() " + n + ".  set to: " + text);
                    sPoints[n] = text;


                    //
                    //update();
                    mFirebaseRef.setValue(sPoints);
                }
            }
        });


        editNumber.setOnFocusChangeListener(new View.OnFocusChangeListener() {

            public void onFocusChange(View v, boolean hasFocus) {
                if (!hasFocus) {
                    Log.d(TAG, "editNumber setOnFocusChangeListener () !hasFocus");
                    //
                    int n = 0;
                    try {
                        n = Integer.parseInt(editNumber.getText().toString());
                    } catch (Exception e) {
                        Log.d(TAG, "Exception " + e.toString());
                    }

                    int size = sPoints.length;
                    if (n >= 0 && n < size) {
                        Log.d(TAG, "Update editDescription to " + sPoints[n]);
                        editDescription.setText(sPoints[n]);
                    }
                } else {
                    editNumber.setText("");
                }
            }
        });
    }

    void update() {
        String points = "Points:\n";

        Log.d(TAG, "update");

        int size = sPoints.length;
        for (int i = 0; i < size; i++) {

            if (sPoints[i] != "") {
                points += "" + i + ". " + sPoints[i] + "\n";
            }
        }

        textPoints.setText(points);
    }

}