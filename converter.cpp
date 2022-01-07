#include <iostream>
#include <vector> 
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int inequal_sign_value(string inequal_sign)
{
	if (inequal_sign == "<")
		return 1;
	else if (inequal_sign == "<=")
		return 2;
	else if (inequal_sign == ">")
		return 3;
	else if (inequal_sign == ">=")
		return 4;
	else
		return -1;
}

int weight_value(string weight)
{
	if (weight == "++")
		return 1;
	else if (weight == "--")
		return 2;
	else
		return -1;
}

int main()
{
	FILE* fp = fopen("c-program.c", "r");
	FILE* wp = fopen("py-program.py", "w+");

	char str[100];
	char new_str[100];
	char new_str2[100];
	char new_str3[100];
	char* rets = NULL;
	char* rets_two = NULL;
	int nullspace = 0;
	int count = 1;

	while (!feof(fp))
	{
		fgets(str, 100, fp);
		strcpy(new_str, str);

		// header transe
		rets = strtok(str, "<");
		if (strcmp("#include ", rets) == 0)
		{
			rets = strtok(NULL, ">");

			if (strcmp("string.h", rets) == 0)
			{
				fprintf(wp, "%s\n", "import string");
				continue;
			}
			else if (strcmp("math.h", rets) == 0)
			{
				fprintf(wp, "%s\n", "import math");
				continue;
			}
			else if (strcmp("random", rets) == 0)
			{
				fprintf(wp, "%s\n", "import random");
				continue;
			}
			else continue;
		}
		strcpy(new_str2, rets);
		strcpy(new_str3, str);
		rets_two = strtok(new_str2, " ");
		if (strcmp("void", rets_two) == 0)
		{
			nullspace = 1;
			fprintf(wp, "\ndef ");
			rets_two = strtok(NULL, "(");
			fprintf(wp, "%s(", rets_two);
			rets_two = strtok(NULL, ",");

			while (rets_two != NULL)
			{
				rets_two = strtok(NULL, ",");

				if (rets_two == NULL)
				{
					count--;
					break;
				}
				count++;
			}

			if (count == 0)
			{
				fprintf(wp, ") : ");
			}
			else
			{
				count++;
				rets_two = strtok(new_str3, "(");
				for (int i = 0; i < count; i++)
				{
					strtok(NULL, " ");
					if (i == count - 1)
					{
						rets_two = strtok(NULL, ")");
						fprintf(wp, "%s) : ", rets_two);
						break;
					}
					rets_two = strtok(NULL, ",");
					fprintf(wp, "%s,", rets_two);
				}
			}
			count = 1;

		}

		//  string -> char c*
		//  char c* -> string

		//semicolen transe
		rets = strtok(str, ";");
		string notspace(rets);
		notspace.erase(notspace.begin());
		vector<char> vc(notspace.begin(), notspace.end());
		vc.push_back('\0');
		rets = &*vc.begin();
		vc.pop_back();

		// return 0 transe
		if (strcmp("return 0", rets) == 0)
			continue;

		rets = strtok(str, "(");
		notspace = rets;
		notspace.erase(notspace.begin());
		vector<char> vc1(notspace.begin(), notspace.end());
		vc1.push_back('\0');
		rets = &*vc1.begin();
		vc1.pop_back();

		rets = strtok(str, " ");
		notspace = rets;
		notspace.erase(notspace.begin());
		vector<char> vc2(notspace.begin(), notspace.end());
		vc2.push_back('\0');
		rets = &*vc2.begin();
		vc2.pop_back();

		//comment transe
		if (strcmp("/", rets) == 0)
		{
			rets = strtok(NULL, "\0");
			fprintf(wp, "\n# %s", rets);
		}//variable transe
		else if (strcmp("int", rets) == 0 || strcmp("float", rets) == 0
			|| strcmp("double", rets) == 0 || strcmp("char", rets) == 0
			|| strcmp("boolean", rets) == 0)
		{
			nullspace = 0;
			rets = strtok(NULL, "=");
			notspace = rets;

			if (notspace.find("[") != string::npos)
			{
				// list transe 
				rets = strtok(rets, "[");
				fprintf(wp, "\n%s", rets);
				if (strstr(new_str, "{") != NULL)
				{
					rets = strtok(new_str, "{");
					rets = strtok(NULL, "}");
					fprintf(wp, " = [%s]", rets);
				}
				else //char[] transe
				{
					rets = strtok(new_str, "]");
					rets = strtok(NULL, ";");
					fprintf(wp, "%s", rets);
				}
			}
			else {
				fprintf(wp, "\n%s", rets);
				rets_two = strtok(new_str, "=");
				rets_two = strtok(NULL, ";");

				notspace = rets_two;
				notspace.erase(notspace.begin());
				vector<char> vc2(notspace.begin(), notspace.end());
				vc2.push_back('\0');
				rets_two = &*vc2.begin();
				vc2.pop_back();

				// true -> True transe
				// false -> Fasle transe
				if (strcmp("true", rets_two) == 0)
					fprintf(wp, "= True");
				else if (strcmp("false", rets_two) == 0)
					fprintf(wp, "= False");
				else
					fprintf(wp, "= %s", rets_two);
			}
		}// print transe
		else if (strcmp("print", rets) == 0)
		{
			if (nullspace == 1)
			{
				fprintf(wp, "\n\t%s", "print(");
				rets = strtok(new_str, "(");
				rets = strtok(NULL, ")");
				fprintf(wp, "%s)", rets);
			}
			else {
				fprintf(wp, "\n%s", "print(");
				rets = strtok(new_str, "(");
				rets = strtok(NULL, ")");
				fprintf(wp, "%s)", rets);
			}
		}
		//printf transe
		else if (strcmp("printf", rets) == 0)
		{
			if (nullspace == 1)
			{
				strcpy(new_str2, new_str);
				fprintf(wp, "\n\tprint(");
				rets = strtok(new_str, "(");
				rets = strtok(NULL, "%");

				rets_two = strtok(new_str2, ",");
				rets_two = strtok(NULL, ")");
				fprintf(wp, "%s{0}\".format(%s))\n", rets, rets_two);
			}
			else {
				strcpy(new_str2, new_str);
				fprintf(wp, "\n%s", "print(");
				rets = strtok(new_str, "(");
				rets = strtok(NULL, "%");

				rets_two = strtok(new_str2, ",");
				rets_two = strtok(NULL, ")");
				fprintf(wp, "%s{0}\".format(%s))\n", rets, rets_two);
			}
		} // scanf -> input transe
		else if (strcmp("scanf", rets) == 0)
		{
			nullspace = 0;
			rets_two = strtok(new_str, "&");
			rets_two = strtok(NULL, ")");
			fprintf(wp, "\n%s", rets_two);
			rets_two = strtok(new_str, "%");
			rets_two = strtok(NULL, "\"");
			if (strcmp("d", rets_two) == 0)
				fprintf(wp, " = int(input())");
			else if (strcmp("f", rets_two) == 0)
				fprintf(wp, " = float(input())");
			else
				fprintf(wp, " = input()");

		}// if transe
		else if (strcmp("if", rets) == 0)
		{
			nullspace = 1;
			if (strstr(new_str, "&&") != NULL)
			{
				rets_two = strtok(new_str, "&&");
				notspace = rets_two;
				notspace.erase(notspace.begin());
				vector<char> vc2(notspace.begin(), notspace.end());
				vc2.push_back('\0');
				rets_two = &*vc2.begin();
				fprintf(wp, "\n\n%s", rets_two);
				rets_two = strtok(NULL, " ");
				if (strcmp("&", rets_two) == 0)
					fprintf(wp, "and ");
				rets_two = strtok(NULL, ")");
				fprintf(wp, "%s) : ", rets_two);
			}
			else if (strstr(new_str, "||") != NULL)
			{
				rets_two = strtok(new_str, "||");
				notspace = rets_two;
				notspace.erase(notspace.begin());
				vector<char> vc2(notspace.begin(), notspace.end());
				vc2.push_back('\0');
				rets_two = &*vc2.begin();
				fprintf(wp, "\n%s", rets_two);
				rets_two = strtok(NULL, " ");
				if (strcmp("|", rets_two) == 0)
					fprintf(wp, "or ");
				rets_two = strtok(NULL, ")");
				fprintf(wp, "%s) : \n", rets_two);
			}
			else
				continue;
		} // else if -> elif transe
		else if (strcmp("else", rets) == 0 || strcmp("else ", rets) == 0)
		{
			nullspace = 1;
			if (strstr(new_str, "else if") != NULL)
			{
				fprintf(wp, "elif (");
				if (strstr(new_str, "&&") != NULL)
				{
					rets_two = strtok(new_str, "(");
					notspace = rets_two;
					notspace.erase(notspace.begin());
					vector<char> vc2(notspace.begin(), notspace.end());
					vc2.push_back('\0');
					rets_two = &*vc2.begin();

					rets_two = strtok(NULL, "&&");
					fprintf(wp, "%s and ", rets_two);
					rets_two = strtok(NULL, " ");
					rets_two = strtok(NULL, ")");
					fprintf(wp, "%s) : ", rets_two);
				}
				else if (strstr(new_str, "||") != NULL)
				{
					rets_two = strtok(new_str, "(");
					notspace = rets_two;
					notspace.erase(notspace.begin());
					vector<char> vc2(notspace.begin(), notspace.end());
					vc2.push_back('\0');
					rets_two = &*vc2.begin();

					rets_two = strtok(NULL, "||");
					fprintf(wp, "%s or ", rets_two);
					rets_two = strtok(NULL, " ");
					rets_two = strtok(NULL, ")");
					fprintf(wp, "%s) : ", rets_two);
				}
				else
					continue;
			}
			else // else transe
			{
				fprintf(wp, "else :");
				if (strstr(new_str, "&&") != NULL)
				{
					rets_two = strtok(new_str, "(");
					notspace = rets_two;
					notspace.erase(notspace.begin());
					vector<char> vc2(notspace.begin(), notspace.end());
					vc2.push_back('\0');
					rets_two = &*vc2.begin();

					rets_two = strtok(NULL, "&&");
					fprintf(wp, "%s and ", rets_two);
					rets_two = strtok(NULL, " ");
					rets_two = strtok(NULL, ")");
					fprintf(wp, "%s) : ", rets_two);
				}
				else if (strstr(new_str, "||") != NULL)
				{
					rets_two = strtok(new_str, "(");
					notspace = rets_two;
					notspace.erase(notspace.begin());
					vector<char> vc2(notspace.begin(), notspace.end());
					vc2.push_back('\0');
					rets_two = &*vc2.begin();

					rets_two = strtok(NULL, "||");
					fprintf(wp, "%s or ", rets_two);
					rets_two = strtok(NULL, " ");
					rets_two = strtok(NULL, ")");
					fprintf(wp, "%s) : ", rets_two);
				}
				else
					continue;
			}
		} // for i in range(start,end,weight) transe
		else if (strcmp("for", rets) == 0)
		{
			nullspace = 1;
			// variable name find
			strtok(new_str, "(");
			strtok(NULL, " ");
			rets = strtok(NULL, " ");
			string variable = rets;

			strtok(NULL, " ");
			rets = strtok(NULL, " ");
			int start = *rets - 48;

			strtok(NULL, " ");
			rets = strtok(NULL, " ");
			string inequal_sign = rets;

			rets = strtok(NULL, ";");
			int end = *rets-48;

			strtok(NULL, variable.c_str());
			rets = strtok(NULL, ")");
			string weight = rets;

			fprintf(wp, "\nfor %s in range(", variable.c_str());
			int inequal_sign_kind = inequal_sign_value(inequal_sign);
			int weight_kind = weight_value(weight);

			if (inequal_sign_kind == 1 && weight_kind == 1)
				fprintf(wp, "%d,%d,1) :", start, end);				// < & ++
			else if (inequal_sign_kind == 2 && weight_kind == 1)
				fprintf(wp, "%d,%d,1) :", start, end + 1);			// <= & ++
			else if (inequal_sign_kind == 3 && weight_kind == 2)
				fprintf(wp, "%d,%d,-1) :", start, end);				// > & -- 
			else if (inequal_sign_kind == 4 && weight_kind == 2)
				fprintf(wp, "%d,%d,-1) :", start, end-1);			// >= & --
			else
				continue;
		}
		else {
			if (strcmp("}", new_str) == 0 && strcmp("{", new_str) == 0)
				fprintf(wp, "\n");
		}
	}

	return 0;
}