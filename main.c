#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include"CDIO_demo.h"

FILE *fp;

int main()
{
    char userName[50],password[50];// sign up purpose
    int Capital_letter=0,Small_letter=0,Digit=0,Punct=0,username_length=0,password_length=0,space=0,x=0,j=0,i=0;
    char health_screening_or_detect_tampering[2],signUp_logIn[2],change_password_or_not[2];
    char userfile[10000],log_in_username[50],log_in_password[50], user1[20], us[20], password1[20], pa[20],IC[15],Name[30],blood_type[10];
    float weight, height, bmi;
    int heart_rate=0,bloodtype,gender,age;
    int blood_glucose, blood_cholesterol;
    int systolic_pressure, diastolic_pressure;
    char genotype1[2], genotype2[2];
    askAgain:printf("Do you want to sign up or log in?\n1)Sign up\n2)Log in\n");
    gets(signUp_logIn);

    if (signUp_logIn[0]=='1'&& signUp_logIn[1]=='\0')//for sign up
    {
        printf("\nSIGN UP\n");
        key_in_username:printf("\n1.Your username must consist of at least 1 Capital letter,1 Small letter,1 digit and 1 symbol(except \\,/,:,*,?,>,|,\").\n2.The length of username must between 6 and 12 characters.\n3.No blank space is allow.\n");
        printf("\nPlease key in your username:\n");
        fflush(stdin);
        gets(userName);

        username_length=strlen(userName);

        for (j=0;j<username_length;j++)
        {
            space=isspace(userName[username_length]);
            if ((space!=0))
            {
                printf("There is an invalid blank space in your username. Please try to key in valid username.");
                goto key_in_username;
            }
        }

        bool result = verification(userName);

        if(result)
        {
            printf("Your username is valid\n");
        }
        else
        {
            printf("Your username is invalid.Please follow the restriction.\n");
            goto key_in_username;
        }
        strcpy(user1,userName);// copy into log in username
        FILE *fp;

    fp = fopen(strcat(user1,".txt"), "r");

    fscanf(fp, "%s", us);

     if(strcmp(userName,us)==0)
        {
            printf("Duplicate Username please reenter\n\n");
            goto askAgain;
        }
        else
        {
            printf("Success!\n");
            goto key_in_password;
        }

    fclose(fp);


        key_in_password:printf("\n1.Your password suggested to consist of at least 1 Capital letter, 1 Small letter, 1 number and 1 Special symbol.\n2.The length of password must be 8.\n3.No blank space is allow.\n");
        printf("\nPlease key in your password:");
        gets(password);

        password_length = strlen(password);

        if (password_length!=8)
        {
            printf("Password length not equal to 8!");
            goto key_in_password;
        }

       for (x=0;x<password_length;x++)
        {
            space=isspace(password[password_length]);
            if ((space!=0))
            {
                printf("There is an invalid blank space in your password. Please try to key in valid password.");
                goto key_in_password;
            }
        }

        for (x=0;x<8;x++)
        {

            if (isupper(password[x]))
            {
                Capital_letter += 1;
            }
            else if (islower(password[x]))
            {
                Small_letter += 1;
            }
            else if (isdigit(password[x]))
            {
                Digit += 1;
            }
            else if (ispunct(password[x]))
            {
                Punct += 1;
            }
            else
            {
                printf("Invalid Password!\n");
                goto key_in_password;
            }
        }

        if (Capital_letter && Small_letter && Digit && Punct)
        {
            printf("Very Strong Password!\n");
        }
        else if ( ((Capital_letter) && (!Small_letter) && (!Digit) && (!Punct)) || ((!Capital_letter) && (Small_letter) && (!Digit) && (!Punct)) || ((!Capital_letter) && (!Small_letter) && (Digit) && (!Punct)) || ((!Capital_letter) && (!Small_letter) && (!Digit) && (Punct)) )
        {
            printf("Very Weak Password!\n");

        }
        else if (((!Capital_letter) && Small_letter && Digit && Punct) || (Capital_letter && (!Small_letter) && Digit && Punct) || (Capital_letter && Small_letter && (!Digit) && Punct) || (Capital_letter && Small_letter && Digit && (!Punct)))
        {
            printf("Strong Password!\n");
        }
        else
        {
            printf("Weak Password!\n");
        }

        password_change_or_not:printf("\nDo you want to change password again? (1)Yes (2)No:");
        gets(change_password_or_not);

        if (change_password_or_not[0]=='1'&&change_password_or_not[1]=='\0')
        {
            fflush(stdin);
            goto key_in_password;
        }
        else if(change_password_or_not[0]=='2'&&change_password_or_not[1]=='\0')
        {
            sprintf(userfile, "%s.txt",userName);
            fp = fopen(userfile, "w");
            fprintf(fp,"%s %s\n",userName,password);
            fclose(fp);
        }
        else
        {
            printf("Invalid choice.Please key in again.\n");
            goto password_change_or_not;
        }

    }

    else if ( (signUp_logIn[0]=='2'&& signUp_logIn[1]=='\0')) // for login
    {
        printf("\nPlease enter the username:");
        fflush(stdin);
        gets(log_in_username);
        printf("Please enter password:");
        gets(log_in_password);
        strcpy(user1, log_in_username);// copy into log in username
        strcpy(password1, log_in_password);
        FILE *fp;
        fp = fopen(strcat(user1,".txt"), "r");
        fscanf(fp, "%s %s", us,pa);

        if(strcmp(log_in_username,us)==0 && strcmp(log_in_password,pa)==0)
        {
            printf("Login successfully\n\n");
            goto askAgain2;
        }
        else
        {
            printf("Incorrect username or password\n\n");
            goto askAgain;
        }

        fclose(fp);

        askAgain2:printf("What do you want to do? (1)Health screening (2)Tampering detection:");
        scanf("%s",health_screening_or_detect_tampering);
system("pause");
system("cls");
        if (health_screening_or_detect_tampering[0]=='1'&&health_screening_or_detect_tampering[1]=='\0')
        { //health screening
            {
                fflush(stdin);
                printf("\n-------------------------------------------------------\n");
                printf("              PATIENT RECORD                           \n");
                printf("-------------------------------------------------------\n");
                printf("Name     :");
                fflush(stdin);
                gets(Name);
                key_in_IC:printf("IC number:");
                gets(IC);
                if(strlen(IC)!=12)
                {
                    printf("Invalid length of IC.Please key in again!\n");
                    goto key_in_IC;
                }

                for (i=0;i<12;i++)
                {
                 if(isdigit(IC[i])!=1)
                 {
                     printf("Invalid IC.Please key in again!\n");
                     goto key_in_IC;
                 }
                }
                printf("\n--------------------\n");
                printf("BMI");
                printf("\n--------------------\n");
                here:printf("Insert Height(m) : ");
                fflush(stdin);

                while(scanf("%f", &height)!=1)
                {
                    goto here;
                }

                if(height<2.2 && height>0)
                {
                    goto here1;
                }
                else
                {
                    goto here;
                }

                here1:printf("Insert Weight(kg): ");
                fflush(stdin);

                while(scanf("%f", &weight)!=1)
                {
                    goto here1;
                }

                if (weight<0 || weight>1000)
                {
                    goto here;
                }

                fflush(stdin);
                bmi = (weight)/(height * height);

            if(bmi>=0 && bmi<16)
                {
                    printf("Your BMI is %.2f\n", bmi);
                    printf("Severely Underweight\n");
                }
            else if(bmi>16 && bmi<=18.5)
                {
                    printf("Your BMI is %.2f\n", bmi);
                    printf("Underweight\n");
                }
            else if(bmi>18.5 && bmi<=24.9)
                {
                    printf("Your BMI is %.2f\n", bmi);
                    printf("Normal\n");
                }
            else if(bmi>=25 && bmi<=29.9)
                {
                    printf("Your BMI is %.2f\n", bmi);
                    printf("Overweight\n");
                }
            else if(bmi>=30)
                {
                    printf("Your BMI is %.2f\n", bmi);
                    printf("Obesity\n");
                }
            else if(bmi<0)
                {
                    printf("Invalid\n");
                    goto here;
                }
            else
                {
                    printf("Invalid\n");
                    goto here;
                }

            printf("\n--------------------\n");
            printf("Heart Rate");
            printf("\n--------------------\n");

            here4:printf("Insert Heart Rate(bpm)           : ");
            fflush(stdin);
            while(scanf("%d", &heart_rate)!=1)
            {
                goto here4;
            }

            if (heart_rate<0)
            {
                goto here4;
            }

            age=age_cdio(IC);
            here5:printf("Insert Gender(1. Male, 2. Female): ");
            fflush(stdin);
            while(scanf("%d", &gender)!=1)
            {
                goto here5;
            }

            if (gender!=1 && gender!=2)
            {
                goto here5;
            }

            if(gender==1)
            {
                if(age>=18 && age<=25)
                    {
                        if(heart_rate>0 && heart_rate<49)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=49 && heart_rate<=55)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=56 && heart_rate<=61)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=62 && heart_rate<=65)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=66 && heart_rate<=69)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=70 && heart_rate<=73)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=81)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=82)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=26 && age<=35)
                    {
                        if(heart_rate>0 && heart_rate<49)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=49 && heart_rate<=54)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=55 && heart_rate<=61)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=62 && heart_rate<=65)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=66 && heart_rate<=70)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=71 && heart_rate<=74)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=75 && heart_rate<=81)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=82)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=36 && age<=45)
                    {
                        if(heart_rate>0 && heart_rate<50)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=50 && heart_rate<=56)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=57 && heart_rate<=62)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=63 && heart_rate<=66)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=67 && heart_rate<=70)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=71 && heart_rate<=75)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=76 && heart_rate<=82)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=83)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=46 && age<=55)
                    {
                        if(heart_rate>0 && heart_rate<50)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=50 && heart_rate<=57)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=58 && heart_rate<=63)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=64 && heart_rate<=67)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=68 && heart_rate<=71)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=72 && heart_rate<=76)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=77 && heart_rate<=83)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=84)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=56 && age<=65)
                    {
                        if(heart_rate>0 && heart_rate<51)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=51 && heart_rate<=56)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=57 && heart_rate<=61)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=62 && heart_rate<=67)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=68 && heart_rate<=71)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=72 && heart_rate<=75)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=76 && heart_rate<=81)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=82)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=66)
                    {
                        if(heart_rate>0 && heart_rate<50)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=50 && heart_rate<=55)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=56 && heart_rate<=61)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=62 && heart_rate<=65)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=66 && heart_rate<=69)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=70 && heart_rate<=73)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=79)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=80)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
            }
            else if(gender==2)
            {
                if(age>=18 && age<=25)
                    {
                        if(heart_rate>0 && heart_rate<53)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=60)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=61 && heart_rate<=65)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=66 && heart_rate<=69)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=70 && heart_rate<=73)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=78)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=79 && heart_rate<=84)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=85)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=26 && age<=35)
                    {
                        if(heart_rate>0 && heart_rate<54)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=59)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=60 && heart_rate<=64)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=65 && heart_rate<=68)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=69 && heart_rate<=72)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=73 && heart_rate<=76)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=77 && heart_rate<=82)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=83)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=36 && age<=45)
                    {
                        if(heart_rate>0 && heart_rate<54)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=59)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=60 && heart_rate<=64)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=65 && heart_rate<=69)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=70 && heart_rate<=73)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=78)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=79 && heart_rate<=84)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=85)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=46 && age<=55)
                    {
                        if(heart_rate>0 && heart_rate<54)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=60)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=61 && heart_rate<=65)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=66 && heart_rate<=69)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=70 && heart_rate<=73)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=77)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=78 && heart_rate<=83)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=84)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=56 && age<=65)
                    {
                        if(heart_rate>0 && heart_rate<54)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=59)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=60 && heart_rate<=64)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=65 && heart_rate<=68)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=69 && heart_rate<=73)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=74 && heart_rate<=77)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=78 && heart_rate<=83)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=84)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
                else if(age>=66)
                    {
                        if(heart_rate>0 && heart_rate<54)
                        {
                            printf("Low Heart Rate\n");
                        }
                        else if(heart_rate>=54 && heart_rate<=59)
                        {
                            printf("Athlete Heart Rate\n");
                        }
                        else if(heart_rate>=60 && heart_rate<=64)
                        {
                            printf("Excellent Heart Rate\n");
                        }
                        else if(heart_rate>=65 && heart_rate<=68)
                        {
                            printf("Great Heart Rate\n");
                        }
                        else if(heart_rate>=69 && heart_rate<=72)
                        {
                            printf("Good Heart Rate\n");
                        }
                        else if(heart_rate>=73 && heart_rate<=76)
                        {
                            printf("Average Heart Rate\n");
                        }
                        else if(heart_rate>=77 && heart_rate<=84)
                        {
                            printf("Below Average Heart Rate\n");
                        }
                        else if(heart_rate>=85)
                        {
                            printf("Poor Heart Rate\n");
                        }
                        else if(heart_rate<0)
                        {
                            printf("Invalid\n");
                            goto here4;
                        }
                    }
            }

            printf("\n--------------------\n");
            printf("Blood Glucose");
            printf("\n--------------------\n");

            here2:printf("Insert Blood Glucose(mg/dL): ");
            fflush(stdin);
            while(scanf("%d", &blood_glucose)!=1)
            {
                goto here2;
            }

            if(blood_glucose>0 && blood_glucose<80)
                {
                    printf("Low Blood Glucose\n");
                }
            else if(blood_glucose>=80 && blood_glucose<=100)
                {
                   printf("Normal\n");
                }
            else if(blood_glucose>100 && blood_glucose<=125)
                {
                    printf("Prediabetes\n");
                }
            else if(blood_glucose>125)
                {
                    printf("Diabetic\n");
                }
            else if(blood_glucose<0)
                {
                    printf("Invalid\n");
                    goto here2;
                }
            else
                {
                    printf("Invalid\n");
                    goto here2;
                }

            printf("\n--------------------\n");
            printf("Blood Pressure");
            printf("\n--------------------\n");

            here3:printf("Insert Systolic Pressure(mmHg): ");
            fflush(stdin);
            while(scanf("%d", &systolic_pressure)!=1)
            {
                goto here3;
            }

            if (systolic_pressure<0)
            {
                goto here3;
            }
            printf("Insert Diastolic Pressure(mmHg): ");
            fflush(stdin);
            while(scanf("%d", &diastolic_pressure)!=1)
            {
                goto here3;
            }

            if(diastolic_pressure<0)
            {
                goto here3;
            }

            if (systolic_pressure<diastolic_pressure)
            {
                printf("Systolic pressure will always higher than diastolic!\n");
                goto here3;
            }

            if((systolic_pressure>=160 && systolic_pressure<=199) || (diastolic_pressure>=100 && diastolic_pressure<=129))
                {
                    printf("Hypertensive Stage 2\n");
                }
           else if((systolic_pressure>=140 && systolic_pressure<=159) || (diastolic_pressure>=90 && diastolic_pressure<=99))
                {
                    printf("Hypertension Stage 1\n");
                }
           else if((systolic_pressure>=120 && systolic_pressure<=139) || (diastolic_pressure>=80 && diastolic_pressure<=89))
                {
                    printf("Pre Hypertension\n");
                }
           else if((systolic_pressure>=90 && systolic_pressure<=119) || (diastolic_pressure>=60 && diastolic_pressure<=79))
                {
                    printf("Normal blood pressure\n");
                }

            else if((systolic_pressure>=70 && systolic_pressure<=89) || (diastolic_pressure>=40 && diastolic_pressure<=59))
                {
                    printf("Low blood pressure\n");
                }
            else if(systolic_pressure<70  || diastolic_pressure<40)
                {
                    printf("Invalid ,please reenter\n");
                    goto here3;
                }
            else if(systolic_pressure>=200 && diastolic_pressure>=200)
                {
                    printf("Invalid, please reenter\n");
                     goto here3;
                }
            else
                {
                   printf("Invalid,please reenter\n");
                    goto here3;
                }


            printf("\n--------------------\n");
            printf("Blood Cholesterol");
            printf("\n--------------------\n");

            here6:printf("Insert Blood Cholesterol(mg/dL): ");
            fflush(stdin);
            while(scanf("%d", &blood_cholesterol)!=1)
            {
                goto here6;
            }

            if(blood_cholesterol>0 && blood_cholesterol<200)
                {
                    printf("Heart-Healthy\n");
                }
            else if(blood_cholesterol>=200 && blood_cholesterol<=239)
                {
                    printf("At-risk\n");
                }
            else if(blood_cholesterol>=240)
                {
                    printf("Dangerous\n");
                }
            else if(blood_cholesterol<0)
                {
                    printf("Invalid\n");
                    goto here6;
                }
            else
                {
                    printf("Invalid\n");
                    goto here6;
                }


            ask_blood:printf("\n--------------------\n");
            printf("Blood Type");
            printf("\n--------------------\n");

            printf("Insert Genotype I: ");
            fflush(stdin);
            gets(genotype1);
            if (genotype1[1]!='\0')
            {
                goto ask_blood;
            }

            printf("Insert Genotype II: ");
            fflush(stdin);
            gets(genotype2);

            if (genotype2[1]!='\0')
            {
                goto ask_blood;
            }

            if(genotype1[0]=='A' && genotype2[0]=='A')
                {
                    bloodtype = 1;
                }
            else if(genotype1[0]=='A' && genotype2[0]=='O')
                {
                    bloodtype = 2;
                }
            else if(genotype1[0]=='O' && genotype2[0]=='A')
                {
                    bloodtype = 3;
                }
            else if(genotype1[0]=='B' && genotype2[0]=='B')
                {
                    bloodtype = 4;
                }
            else if(genotype1[0]=='B' && genotype2[0]=='O')
                {
                    bloodtype = 5;
                }
            else if(genotype1[0]=='O' && genotype2[0]=='B')
                {
                    bloodtype = 6;
                }
            else if(genotype1[0]=='A' && genotype2[0]=='B')
                {
                    bloodtype = 7;
                }
            else if(genotype1[0]=='B' && genotype2[0]=='A')
                {
                    bloodtype = 8;
                }
            else if(genotype1[0]=='O' && genotype2[0]=='O')
                {
                    bloodtype = 9;
                }
            else
                {
                    bloodtype = 0;
                }


            if (bloodtype==1 || bloodtype==2 || bloodtype==3)
                {
                 printf("Your Blood Type is A\n");
                  blood_type[0]='A';
            }
            else if (bloodtype==4 || bloodtype==5 ||bloodtype==6)
                {
                 printf("Your Blood Type is B\n");
                    blood_type[0]='B';
            }
            else if (bloodtype==7 || bloodtype==8)
                {
                   printf("Your Blood Type is AB\n");
                     blood_type[0]='A';
                     blood_type[1]='B';
            }
            else if (bloodtype==9)
                {
                    printf("Your Blood Type is O\n");
                     blood_type[0]='O';
            }
            else
                {
                printf("Please key in correct blood type!\n");
                goto ask_blood;
            }
                }

             caesarCipherDecrypt();
             fp=fopen("patient_info.csv", "a+");
             fprintf(fp,"%s,%s,%.2f,%.2f,%d,%s,%d,%d,%d/%d\n",Name,IC,weight,height,heart_rate,blood_type,blood_glucose,blood_cholesterol,systolic_pressure,diastolic_pressure);
             fclose(fp);
             caesarCipherEncrypt();
             sha_1_1();

        }//health screening
        else if (health_screening_or_detect_tampering[0]=='2'&&health_screening_or_detect_tampering[1]=='\0')
        {
             sha_1_2();
             caesarCipherDecrypt();
             //caesarCipherEncrypt();
        }
        else
        {
            goto askAgain2;
        }
    }

    else //for error control of sign up or log in
    {
        printf("Invalid choice.Please key in again.\n");
        goto askAgain;
    }
    return 0;

}






























