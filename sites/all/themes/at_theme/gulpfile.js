// Include gulp
var gulp = require('gulp');

// Include Our Plugins
var autoprefixer = require("gulp-autoprefixer");
var concat = require("gulp-concat");
var jshint = require("gulp-jshint");
var less = require("gulp-less");
var minifycss = require("gulp-minify-css");
var notify = require("gulp-notify");
var rename = require("gulp-rename");
var sass = require("gulp-ruby-sass");
var serve = require("gulp-serve");
var sourcemaps = require("gulp-sourcemaps");
var uglify = require("gulp-uglify");
var path = require('path');

// Lint Task
gulp.task('lint', function() {
    return gulp.src('custom-js/source/*.js')
        .pipe(jshint())
        .pipe(jshint.reporter('default'))
        .pipe(notify({message: "JS checked"}));
});

gulp.task('less', function() {
    gulp.src(['less/main.less'])
        .pipe(less())
        .pipe(autoprefixer('last 2 version', 'safari 5', 'ie8', 'ie 9', 'opera 12.1', 'ios 6', 'android 4'))
        .pipe(gulp.dest('css'))
        .pipe(minifycss())
        .pipe(rename('main.min.js'))
        .pipe(gulp.dest('css'))
        .pipe(notify({message: "LESS compiled"}));
})

// Concatenate & Minify JS
gulp.task('scripts', function() {
    return gulp.src('custom-js/source/*.js')
        .pipe(concat('all.js'))
        .pipe(gulp.dest('custom-js/build'))
        .pipe(rename('all.min.js'))
        .pipe(uglify())
        .pipe(gulp.dest('custom-js/build'))
        .pipe(notify({message: "JS minified"}));
});

gulp.task('watch', function() {
    gulp.watch('js/*.js', ['lint', 'scripts']);
    gulp.watch('less/*.less', ['less']);
});

gulp.task('default', ['lint', 'less', 'scripts', 'watch']);