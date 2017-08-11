<!DOCTYPE html>
<html lang='en'>
<head>
</head>

<body class='ui_mars  project' data-page='projects:blob:show' data-project-id='13711'>

<h1 id="project-instruction">Project Instruction<a href="#project-instruction"></a></h1>&#x000A;&#x000A;
<h2 id="before-you-start">Before you start<a href="#before-you-start"></a></h2>&#x000A;
<p>Please be aware that <strong>YOU SHOULD BE ONLY WORKING UNDER THE DIRECTORY THAT IS NAMED AFTER YOU</strong>. 
For different stages, work under different directories.
</p>&#x000A;
<h2 id="how-to-work-on-the-project-git">How to work on the project (Git)
<a href="#how-to-work-on-the-project-git"></a></h2>&#x000A;<ol>&#x000A;
<li>First you will need to clone this repository into your computer, so do the following:&#x000A;&#x000A;<ol>&#x000A;
<li>Change working directory to <em>where you want to store your working repository</em> by using <code>cd</code> command. If you need to check your working directory, use <code>pwd</code> command (for Unix-like terminal emulator) or 
<code>dir</code> command (for Windows).</li>&#x000A;<li>Clone the remote repository into your own computer. To do this, you will need to use <code>git clone</code> command just like you did for every programming assignment.
</li>&#x000A;<li>Change working directory to the directory you just fetched from the remote server. 
Now in the directory you will be able to see this document ("README.MD").</li>&#x000A;</ol></li>&#x000A;<li>Now it's time for you to create your own branch. When you clone this project to your own computer, you are by default working on the 
<code>master</code> branch. <em>But</em> as the <code>master</code> branch is not for personal editing you will be creating your own branch so you can work burden-freely. To achieve this do the following:&#x000A;&#x000A;<ol>&#x000A;<li>You will now be creating a new branch and switching to that branch. There is a shortcut for doing that: <code>git checkout -b &lt;branch-name&gt;</code>, and if you don't see a comment saying switching successfully, you probably did something wrong.</li>&#x000A;<li>
Now you are working on the new branch. If you want to check which branch you are working on currently, type <code>git branch</code>. In this case you will be seeing at least two branches as you just created one other than <code>master</code> branch.</li>&#x000A;</ol></li>&#x000A;<li>For the first time if you want to push it to remote repository, you will have to 
<code>commit</code> everything as before, and then use <code>git push</code> command followed by two parameters.
 The first one should be <code>https://gitlab.doc.ic.ac.uk/lab1415_summer/arm11_2.git</code> or <code>origin</code> (But check first if <code>origin</code> is <code>https://gitlab.doc.ic.ac.uk/lab1415_summer/arm11_2.git</code> otherwise you will push to some other repository! Check using <code>git remote -v</code>), meaning the current working branch (<em>at this moment you will probably need to check the current working branch by using 
 <code>git branch</code></em>) you are on, and the second one should be the branch name you set for your branch. And voila!</li>&#x000A;</ol>&#x000A;</div>

</article>
</div>

</div>
<div class='modal hide' id='modal-remove-blob'>
<div class='modal-dialog'>
<div class='modal-content'>
<div class='modal-header'>
<a class='close' data-dismiss='modal' href='#'>×</a>
<h3 class='page-title'>Remove README.md</h3>
<p class='light'>
From branch
<strong>master</strong>
</p>
</div>
<div class='modal-body'>
<form accept-charset="UTF-8" action="/g1416301/malware-group-topic/blob/master/README.md" class="form-horizontal" method="post"><div style="display:none"><input name="utf8" type="hidden" value="&#x2713;" /><input name="_method" type="hidden" value="delete" /><input name="authenticity_token" type="hidden" value="/SarseYSPUqExcPaVdHGleGQNKU9kuaBCprPH6h+BBo=" /></div>
<div class='form-group commit_message-group'>
<label class="control-label" for="commit_message">Commit message
</label><div class='col-sm-10'>
<div class='commit-message-container'>
<div class='max-width-marker'></div>
<textarea class="form-control" id="commit_message" name="commit_message" placeholder="Removed this file because..." required="required" rows="3">
</textarea>
</div>
</div>
</div>

<div class='form-group'>
<div class='col-sm-2'></div>
<div class='col-sm-10'>
<button class="btn btn-remove btn-remove-file" name="button" type="submit">Remove file</button>
<a class="btn btn-cancel" data-dismiss="modal" href="#">Cancel</a>
</div>
</div>
</form>

</div>
</div>
</div>
</div>
<script>
  disableButtonIfEmptyField('#commit_message', '.btn-remove-file')
</script>


</div>
</div>
</div>
</div>
</div>

<script>
  (function() {
    $('.page-sidebar-collapsed .nav-sidebar a').tooltip({
      placement: "right"
    });
  
  }).call(this);
</script>

</body>
</html>
