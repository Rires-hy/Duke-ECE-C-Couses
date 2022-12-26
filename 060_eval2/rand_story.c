#include "rand_story.h"
#define TRUE 1
#define FALSE -1
//read the raw data from text,and return the starr which stored the information
Read_t ReadRaw(FILE * f) {
  char * line = NULL;
  size_t size = 0;
  Read_t input;
  input.strarr = NULL;
  input.row = 0;

  while (getline(&line, &size, f) >= 0) {
    //store the information use realloc according to the getline 'size'
    input.strarr = realloc(input.strarr, (input.row + 1) * (sizeof(*input.strarr)));
    input.strarr[input.row++] = line;
    line = NULL;
  }
  //free this line
  free(line);
  return input;
}

//pirnt each line of text
void outputStory(Read_t Rtxt) {
  for (size_t n = 0; n < Rtxt.row; n++) {
    printf("%s", Rtxt.strarr[n]);
  }
}

//free the string
void freeString(Read_t Rtxt) {
  for (size_t n = 0; n < Rtxt.row; n++) {
    free(Rtxt.strarr[n]);
  }
  free(Rtxt.strarr);
}

//find the underscore after the black, and check validation
char * parseAid(char * line, int * i) {
  char * catName = NULL;
  int k = 0;
  if (strchr(line, '_') == NULL) {
    fprintf(stderr, "There is no underscore after blank\n");
    exit(EXIT_FAILURE);
  }
  while (line[*i] != '_') {
    catName = realloc(catName, (k + 1) * sizeof(*catName));
    catName[k] = line[*i];
    *i = *i + 1;
    k++;
  }
  return catName;
}

//read the struct of Read_t and change the blank
void parse(Read_t Raw) {
  char * befCat = NULL;
  char * aftCat = NULL;
  char * catName = NULL;
  int gap = 0;
  size_t catNamelen = 0;
  //go through each line
  for (size_t j = 0; j < Raw.row; j++) {
    // if there still are '_' exists, substitude the blank.
    while (strchr(Raw.strarr[j], '_') != NULL) {
      //find the position of two '_'
      befCat = strchr(Raw.strarr[j], '_');
      aftCat = strchr(befCat + 1, '_');
      //check for invalid underscore.
      if (aftCat == NULL) {
        fprintf(stderr,
                "There is no underscore after one underscore or the number is odd!\n");
        exit(EXIT_FAILURE);
      }
      //create catName to store the read content form blank
      catName = malloc((aftCat - befCat) * sizeof(*catName));
      strncpy(catName, befCat + 1, aftCat - befCat - 1);
      //lenth
      catNamelen = aftCat - befCat - 1;
      //gave the
      const char * SUB = chooseWord(catName, NULL);
      gap = catNamelen + 2 - strlen(SUB);
      free(catName);
      //set the lenth of new line and malloc memory
      size_t Parsedsize = strlen(Raw.strarr[j]) - gap;
      char * Parsedline = malloc((Parsedsize + 1) * sizeof(*Parsedline));
      //create a pointer to go through the parsedline and combine
      char * Parsed = Parsedline;
      //replace before the catName
      char * raw = Raw.strarr[j];
      while (raw < befCat) {
        *Parsed = *raw;
        Parsed++;
        raw++;
      }
      //replace the catName
      while (*SUB != '\0') {
        *Parsed = *SUB;
        Parsed++;
        SUB++;
      }
      //replace after the catName
      char * rightStart = aftCat + 1;
      while (*rightStart != '\0') {
        *Parsed = *rightStart;
        Parsed++;
        rightStart++;
      }
      //after the last Parsed++, add '\0' to the end of line,
      // otherwise there would be another line when print cat
      *Parsed = '\0';
      //free in input string
      free(Raw.strarr[j]);
      Raw.strarr[j] = Parsedline;
    }
  }
}

//check if there were existed cat
int checkRepeat(catarray_t * cat, char * line) {
  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(cat->arr[i].name, line) == 0) {
      return i;
    }
  }
  return FALSE;
}

//separate the words before and after the ":", store them in cat
void step2process(Read_t words, catarray_t * cat) {
  char * Col = NULL;
  char * end = NULL;
  //go through each line of words
  for (size_t i = 0; i < words.row; i++) {
    if (strchr(words.strarr[i], ':') != NULL) {
      //find the position of ":" and the next line char
      Col = strchr(words.strarr[i], ':');
      end = strchr(words.strarr[i], '\n');
      //if there are another ":" found after the first colon, report error
      if (strchr(Col + 1, ':') != NULL) {
        fprintf(stderr, " more than one colon\n");
        exit(EXIT_FAILURE);
      }
      //store the pointer of char before the ":"
      char * catName = strndup(words.strarr[i], Col - words.strarr[i]);
      //store the pointer of char after the ":"
      char * catWord = strndup(Col + 1, end - Col - 1);
      //replace the end char to be '\0'
      if (strchr(catWord, '\n')) {
        char * pch = strchr(catWord, '\n');
        *pch = '\0';
      }
      //store the line in cat
      storeCat(cat, catName, catWord);
    }
    //error if no colon
    else {
      fprintf(stderr, " no colon\n");
      exit(EXIT_FAILURE);
    }
  }
}

//store the catName and catWord by comparing then with cat
void storeCat(catarray_t * cat, char * catName, char * catWord) {
  int check = checkRepeat(cat, catName);
  //if there is same category name found:
  if (check != FALSE) {
    //realloc the memory according to its n_words
    cat->arr[check].words =
        realloc(cat->arr[check].words,
                (cat->arr[check].n_words + 1) * sizeof(*cat->arr[check].words));
    //the new pointer point to catword
    cat->arr[check].words[cat->arr[check].n_words] = catWord;
    //increase the size of the category
    cat->arr[check].n_words++;
    //free catName
    free(catName);
  }
  else {
    //if there is no exited category name find,create a new one
    //memory size = previous size +1
    cat->arr = realloc(cat->arr, (cat->n + 1) * sizeof(*cat->arr));
    //the new line point to catName
    cat->arr[cat->n].name = catName;
    cat->arr[cat->n].words = malloc(sizeof(*cat->arr[cat->n].words));
    //assign the words point to catWord
    cat->arr[cat->n].words[0] = catWord;
    cat->arr[cat->n].n_words = 1;
    //increase the size of the existed categroy
    cat->n++;
  }
}

//free catarr
void freeCatarr(catarray_t * catFree) {
  for (size_t i = 0; i < catFree->n; i++) {
    free(catFree->arr[i].name);
    for (size_t j = 0; j < catFree->arr[i].n_words; j++) {
      free(catFree->arr[i].words[j]);
    }
    free(catFree->arr[i].words);
  }
  free(catFree->arr);
  free(catFree);
}

//check if the catName is digit
int Ifdigit(char * line) {
  while (*line != '\0') {
    if (!isdigit(*line)) {
      return 0;
    }
    line++;
  }
  return 1;
}

//free categroty_t previous
void freePrevious(category_t * previous) {
  for (size_t i = 0; i < previous->n_words; i++) {
    free(previous->words[i]);
  }
  free(previous->words);
}

//update prvious char after changing the blank
void loadPrevious(category_t * previous, char * SUB) {
  (previous)->words = realloc((previous)->words,
                              ((previous)->n_words + 1) * sizeof(*((previous)->words)));
  (previous)->words[(previous)->n_words] = SUB;
  (previous)->n_words++;
}

//Parse Process for step 3, replace the black according to cats
void ParseProcess(Read_t Raw, catarray_t * cats) {
  //setup the pointer of each '_' and catName, catWord
  char * befCat = NULL;
  char * aftCat = NULL;
  char * SUB = NULL;
  char * catName = NULL;

  //crease struct of previous store the previous used word
  category_t previous;
  previous.name = NULL;
  previous.words = NULL;
  previous.n_words = 0;

  //go through each line
  for (size_t j = 0; j < Raw.row; j++) {
    // if there still are '_' exists, substitude the blank.
    while (strchr(Raw.strarr[j], '_') != NULL) {
      //find the position of each "_":
      befCat = strchr(Raw.strarr[j], '_');
      aftCat = strchr(befCat + 1, '_');
      //deep copy the value between these 2 '_' to catName
      catName = strndup(befCat + 1, aftCat - befCat - 1);
      //judge if this catName is digit or alpha character
      if (Ifdigit(catName)) {
        //convert the name to digit
        int digit = atoi(catName);
        //make sure the digit less than the length of used word
        if (!(digit < 1) || (digit > (&previous)->n_words)) {
          //drag out the previous used value according to digit
          SUB = strdup((&previous)->words[(&previous)->n_words - digit]);
          //change the blank to that previous value
          Raw.strarr[j] = ChangeBlank(SUB, Raw.strarr[j], befCat, aftCat);
          //update the used value in previous category
          loadPrevious(&previous, SUB);
        }
        //error if invalid digit number
        else {
          fprintf(stderr, " invalid digit number\n");
          exit(EXIT_FAILURE);
        }
      }
      //if there is existed same catName in cat
      if (checkRepeat(cats, catName) != -1) {
        //get the number of the corressponding value
        int digit = checkRepeat(cats, catName);
        //choose a word from 'choosWord' funciton
        SUB = strdup(chooseWord(cats->arr[digit].name, cats));
        //error if cannot find this name
        if (SUB == NULL) {
          fprintf(stderr, " cannot find this cat!\n");
          exit(EXIT_FAILURE);
        }
        //change the blank to that previous value
        Raw.strarr[j] = ChangeBlank(SUB, Raw.strarr[j], befCat, aftCat);
        //update the used value in previous category
        loadPrevious(&previous, SUB);
      }

      free(catName);
    }
  }
  // free previous category
  freePrevious(&previous);
}

//replace the blank according to the give position of 2 "_" and the Word to substitude
char * ChangeBlank(const char * SUB, char * str, char * befCat, char * aftCat) {
  //decide the length of catName
  size_t catNamelen = aftCat - befCat - 1;
  //the gap between the result line and the raw line after reduce the "_"
  int gap = catNamelen + 2 - strlen(SUB);
  size_t Parsedsize = strlen(str) - gap;
  //allocate memory for parsedline
  char * Parsedline = malloc((Parsedsize + 1) * sizeof(*Parsedline));

  char * Parsed = Parsedline;

  //replace before the catName
  char * raw = str;
  while (raw < befCat) {
    *Parsed = *raw;
    Parsed++;
    raw++;
  }
  //replace the catName
  while (*SUB != '\0') {
    *Parsed = *SUB;
    Parsed++;
    SUB++;
  }
  char * rightStart = aftCat + 1;
  //replace after the catName
  while (*rightStart != '\0') {
    *Parsed = *rightStart;
    Parsed++;
    rightStart++;
  }
  //after the last Parsed++, add '\0' to the end of line,
  // otherwise there would be another line when print cat
  *Parsed = '\0';
  //free in input string
  free(str);
  //return the new string after parsed
  return Parsedline;
}
