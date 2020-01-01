# Notes on data

For simplicity, the data described here are to be considered similar to training data in [machine learning](https://en.wikipedia.org/wiki/Machine_learning) (even if their role may seem different). They are not to be treated either as "input data", "validation data", nor "test data".

There is only one dataset as of December 31, 2019.

## Dataset from the English Wikipedia

### Raw dataset

The raw dataset consists of a list of articles from the English Wikipedia. It is some metadata and text content; there are no multimedia – images etc.

The set is dated on December 20, 2019.

The set has been downloaded in December 2019 by courtesy of [Wikimedia Foundation](https://en.wikipedia.org/wiki/Wikimedia_Foundation) from this website: https://dumps.wikimedia.org/enwiki/20191220/

### Processed data

To be used by the application, the raw dataset must have been processed.

#### Processing phases

There are three phases of processing, in the order presented in the following table. The output of each of them is the input of the next one, except the last one.

Phase no.|Description|Input description|Input format|Output description|Output format|Remarks
-|-|-|-|-|-|-
1|Extracting the content of every article from the raw dataset|A list of English Wikipedia artiles; for each article, the list contains its whole text content and some of its metadata|One text file; the content of it in Wikipedia-specific XML format; the encoding of it: \[TODO\]|A list of English Wikipedia artiles; for each article, the list contains its whole text content, without its metadata|List of text files; the content of each of them in Wikipedia-specific XML format; the enconding of each of them: \[TODO\]|
2|Extracting words from the extracted articles' content|\[TODO\]|\[TODO\]|\[TODO\]|\[TODO\]|
3|Structuring and filtering the words in order they be meaningful for the application|\[TODO\]|\[TODO\]|\[TODO\]|\[TODO\]|The size of the output dataset from this phase must be less or equal to 100MB; this is in order that it will be reasonably easy for others to download the repository; note that this limit easily fits the [GitHub's repository size limitations](https://help.github.com/en/github/managing-large-files/what-is-my-disk-quota#file-and-repository-size-limitations)

#### Processing scripts

For each phase, there is a separate script for handling it. In the following table there are presented their details:

Phase no.|Script technologies|Remarks
-|-|-
1|C|Compiler: GCC 9.2.1 20190827 (Red Hat 9.2.1-1) (GCC); compiled with `gcc -g -lm -Wall -std=gnu99 -Wextra -Wpedantic -Wmissing-prototypes -Wold-style-definition [script-name]` — Operating system: Linux 5.3.16-200.fc30.x86_64 (Fedora 30)
2|\[TODO\]|
3|\[TODO\]|