package osotn.gl.com.customlistview;

import android.content.res.Resources;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    ListView list;
    CustomAdapter adapter;
    public MainActivity CustomListView = null;
    public ArrayList<ListModel> CustomListViewValuesArr = new ArrayList<ListModel>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        CustomListView = this;

        setListData();

        Resources res = getResources();
        list = (ListView)findViewById(R.id.list);

        adapter = new CustomAdapter(CustomListView, CustomListViewValuesArr, res);
        list.setAdapter( adapter );
    }

    public void setListData() {
        for (int i = 0; i < 40; i++) {
            final ListModel sched = new ListModel();

            sched.setCompanyName("Music "+i);
            sched.setImage("image"+i);
            sched.setUrl("http:\\www."+i+".com");

            CustomListViewValuesArr.add(sched);
        }
    }

    public void onItemClick(int mPosition) {
        ListModel tempValues = (ListModel) CustomListViewValuesArr.get(mPosition);

        Toast.makeText(CustomListView, ""+tempValues.getCompanyName()+
                "Image :"+tempValues.getImage()+"Url:"+tempValues.getUrl(),
                Toast.LENGTH_LONG).show();

    }
}
