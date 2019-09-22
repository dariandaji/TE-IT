import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class Reduce extends Reducer <Text, IntWritable, Text, IntWritable> {
	public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
		int max = Integer.MIN_VALUE;
		for(IntWritable val : values )
			if(max<val.get())
				max = val.get();
		context.write(key, new IntWritable(max));
	}
}
