import java.io.IOException;
//import org.apache.hadoop.io.IntWritable;
//import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.*;
//import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.*;

public class LogReducer extends Reducer <Text, IntWritable, Text, IntWritable> {
	public void reduce (Text key, Iterable <IntWritable> values, Context context) throws IOException, InterruptedException {
		int cnt = 0;
		for(IntWritable val : values)
				cnt+=val.get();
		IntWritable count = new IntWritable(cnt);
		context.write(key, count);			
	}
}
