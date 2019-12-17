CSC 281 Final project Report 

Collaborators: Abdelrahman Abdelkader, Yixin Zhang, Sihao Liu

We choose to implement the encryption of the longest common subsequence (LCS) shared between the two inputs of Alice and Bob. The LCS is a very famous problem that is implemented in a lot of real-life applications. LCS is heavily used in biological research: deciding whether two strings of DNA are homologous as well as helping in predicting exons on a target human species. Moreover, it is used to compare big files or data sets. 

In the case that the files or datasets containing  sensitive information are compared with one another, the encryption of this shared information is a necessity. For example, think about the case where a flight agency has a list of travelers on their flights and the FBI that has list of people they want to investigate. Given that these tables are organized in similar order (ex. Name, DOB, Nationality, …..), the securely encrypted LCS will help both parties find the people in both lists without revealing everybody else (This example was provided in class as what can encryption do for us).

In the case of biological research, it might not be as sensitive as the previous example, However in some scenarios where if a human target doesn’t want its DNA string to be revealed unless it matches some other DNA string in query, then using secure encryption will be a great asset.


Implementations:
INPUT:
In the original emp-toolkit, user enter “./<programe> <party> <port> <bitsize>” to start the execution. For the purpose of testing, we changed our argument to “./<programe> <party> <port> <input>” so that the user can directly enter the string to be evaluated on. This is done by generating a txt file for each party, using std input method to write arg[3] into the txt file, and read lines to get the input of the other party. 
ENCAPSULATION:
If we directly pass in argument as string for our securly-computed function(i.e. edit distance and longest subsequence), our input would not be encapsulated. We need to convert that into the Integer object provided in emp-toolkit. Thus we cast the string input to int using ASCII, then do the following:
	Integer a[m];
	for(int i = 0; i < m; i++){
	a[i] = Integer(32, input_a[i], ALICE)
}
		where 32 is the bitsize and PUBLIC means this is ALICE’s input gate. 
CALCULATION:
We use dynamic programming to calculate both edit distance and longest subsequences, since we cannot use recursive method. The dp array is initialized as the following:
Integer dp[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; i++){
		dp[i][j] = Integer(32, input_a[i], PUBLIC);
	}
}
The Integer object is constructed with PUBLIC argument because it’s not belonging to either Alice of Bob, and it’s probably one line in the garble circuit generated from the botton of the toolkit. First a two dimensional array is initialized with the emp Integer object, and the array is filled up with a button-up fashion. Comparison is make to build up different cases. For comparison specifically, the emp-toolkit use operants overload to accomplish the evaluation. 



We encounter a problem for flow control because the “>”, “<”, “==” operators return a bit, but the “if” overloading takes in a boolean value. Since everything has its underlying circuit correspondence and has been overridden by emp, it really took us a long time figuring out how to solve this. So we do:
	if((a[i][j] == b[i][j]).reveal<bool>()) {
//update dp array…...
}
At the end of the nested for loop, the dp array should be filled. We reveal and print the result.
	cout << dp[m][n].reveal<int>() << endl;
 

References: https://pdfs.semanticscholar.org/0e70/095c7bbc636d280760d66a9140ff26a3628f.pdf
