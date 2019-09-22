echo "Enter name of file : "
read adb
if [ -f $adb ]
then 
	echo "file already exist"
else
	echo "Roll No.|Name|Phone|Address" > $adb
fi

insert()
{
        echo "Enter Name"
        read name
        echo "Enter phone"
        read phone
        echo "Enter address"
        read address
        echo "$RollNo|$name|$phone|$address" >> $adb
        echo "Record inserted successfully"
}

modify()
{
	grep -v -w $RollNo $adb > tempdb
	echo "Enter name : "
	read name
	echo "Enter phone : "
	read phone
	echo "Enter address : "
	read address
	cat tempdb > $adb
	echo "$RollNo|$name|$phone|$address" >> $adb
}

delete()
{
	grep -v -w $RollNo $adb > tempdb
	cat tempdb > $adb
	echo "Record deleted successfully."
}
while ( true )
do
	echo "1.Insert Record 2.View Record 3.Modify Record 4.Delete Record 5.View all"
	echo "Enter your choice"
	read ch
	case $ch in
	1)
			echo "Enter Roll No. : "
			read RollNo
			if ( grep -w $RollNo $adb )
			then
				echo "Roll No already present"
			else
			      insert $RollNo
			fi
		;;
		
	2)
		echo "Enter roll no. : "
		read RollNo
		if( grep -w $RollNo $adb )
		then
			echo " "
		else
			echo "Record not present."
		fi
		;;
	3)
		echo "Enter Roll No. : "
		read RollNo
		if( grep -w $RollNo $adb)
		then
			modify $RollNo
		else
			echo "Record not found."
		fi
		;;
	4)
		echo "Enter Roll No. : "
		read	RollNo
		if( grep -w $RollNo $adb)
		then
			delete $RollNo
		else
			echo "Record not found."
		fi
		;;
	5)
		cat $adb
		;;
		
	*)
		echo "Invalid choice"
	esac
done
