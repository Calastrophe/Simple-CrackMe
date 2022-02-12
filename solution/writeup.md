# CrackMe Write-Up

For the first step in nearly any CrackMe, it is to run the file and get a feel for what you need to find ( to crack ).

![Screenshot 2022-02-11 222034](https://user-images.githubusercontent.com/74928681/153696285-073b522b-ac0e-44d2-bb14-05ae99cd242f.png)

After just simply submitting the generated text, we are aware that we need to either find the needed text or somehow get around that check.

Now what is usually running in my head in this situation before even hitting the debugger is to grasp an idea of what you expect.

Sure, you don't know if the strings are decrypted at run-time, but so far we can assume there is some strncmp() function that is comparing our input with a presumed stored value.

So, with this thought in hand, we will crack open x32dbg ( because 32-bit process ) and attach the debugger to the process.

After attaching, right click anywhere inside the instructions, head to "search for" - "all modules" - and "string references".

![Screenshot 2022-02-11 222619](https://user-images.githubusercontent.com/74928681/153696413-84f7d6b2-ebb0-4ced-b2db-01b3ad2db930.png)

After the strings are produced, instantly we have some interesting stuff that looks like a unique key ( but its not ).

Double click on the '408a65c6-665f-44' string and we should be brought to the general area of the strncmp() presumably.

Scroll around and try to find the strncmp near it.

![Screenshot 2022-02-11 225422](https://user-images.githubusercontent.com/74928681/153697270-9e90a780-a1e1-4a15-8823-8cab8a43f5c3.png)

After finding the strncmp, we can see there is a JNE instruction right below it.

This instructions essentially boils down to "jump if cmp is not equal to", which we could theoretically change to get our presumed output of a flag.

So we know that these strings have to match to get our flag, so we can produce some psuedocode.

We have two strings that are compared strncmp(user_input, stored_key) == 0 encased in an if statement, so why don't we just change the JNE to a JE.

This would be the same as strncmp(user_input, stored_key) != 0, essentially making it always work (unless you had the correct key).


![Screenshot 2022-02-11 230110](https://user-images.githubusercontent.com/74928681/153697443-5c62345a-3049-4a2e-a0f5-03f4ee3aa674.png)


So after changing the instruction live while debugging, you can instantly get the result.

You change the instruction by simply tapping the space bar and removing 'n' from jne and hitting OK.

![Screenshot 2022-02-11 230139](https://user-images.githubusercontent.com/74928681/153697453-0d5432c5-d48d-4b01-a9c2-99260c320ded.png)

Now with the same input, we have the flag!
