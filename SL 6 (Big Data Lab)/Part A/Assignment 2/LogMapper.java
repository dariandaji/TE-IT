import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class LogMapper extends Mapper <LongWritable, Text, Text, IntWritable> {
	static IntWritable one = new IntWritable(1);
	
	public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
		String temp = value.toString();
		String[] store = temp.split("-");
		Text word = new Text(store[0]);
		context.write(word,one);
	}
}
