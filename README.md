# Sleep Module for mruby
mruby sleep kernel function

## install by mrbgems
 - add conf.gem line to `build_config.rb`
```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :git => 'https://github.com/pbosetti/mruby-sleep.git'
end
```

## example

```ruby
sleep(10) # sleeps 10 seconds
sleep(0.1) # sleeps 1/10th of a second
sleep(2.5) # sleeps 2 seconds an a half, returns the actual number of seconds slept, rounded to Fixnum
```

# License
under the MIT License:

* http://www.opensource.org/licenses/mit-license.php


