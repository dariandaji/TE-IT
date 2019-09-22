import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class Map extends Mapper <LongWritable, Text, Text, IntWritable> {
	public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
		String str = value.toString();
		String year = str.substring(15,19);
		int temp;
		if(str.charAt(87)=='+')
			temp = Integer.parseInt(str.substring(88, 92));
		else temp = Integer.parseInt(str.substring(87, 92));
		String quality = str.substring(92, 93);
		if(temp !=9999 && quality.matches("[01459]"))
			context.write(new Text(year), new IntWritable(temp));
	}
}
