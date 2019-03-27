<template>
<div class="block">
    <div class="input-card" v-show="onsearch"> 
    <search-card v-if="onsearch" @search="onSubmit"></search-card>
  </div>
     <transition name="el-zoom-in-top">
       <div v-show="onresultShow" class="transition-box"> 
          <search-result v-if="onresultShow" @onback="onBack" @oninit="onInit"></search-result>
       </div>
     </transition>
</div>
</template>

<script>
  import SearchCard from './Controls/SearchCard.vue'
  import SearchResult from './Controls/SearchResult.vue'
  export default {
    name: 'main-page',
    components: {
      SearchCard, SearchResult
    },
    methods: {
      open (link) {
        this.$electron.shell.openExternal(link)
      },
      onSubmit (departure, arrival, departureDate) {
        // alert('submit!    ' + departure)
        this.onsearch = false
        this.onresultShow = true
        this.form.departureDate = departureDate
      },
      onBack () {
        this.onresultShow = false
        this.onsearch = true
      },
      onInit (date) {
        console.log(this.form.departureDate)
      }
    },
    data () {
      return {
        onsearch: true,
        onresultShow: false,
        resultData: '999',
        pickerOptions1: {
          disabledDate (time) {
            return time.getTime() > Date.now()
          },
          shortcuts: [{
            text: '今天',
            onClick (picker) {
              picker.$emit('pick', new Date())
            }
          }, {
            text: '明天',
            onClick (picker) {
              const date = new Date()
              date.setTime(date.getTime() + 3600 * 1000 * 24)
              picker.$emit('pick', date)
            }
          }, {
            text: '一周后',
            onClick (picker) {
              const date = new Date()
              date.setTime(date.getTime() + 3600 * 1000 * 24 * 7)
              picker.$emit('pick', date)
            }
          }]
        },
        form: {
          departure: '',
          arrival: '',
          departureDate: ''
        }
      }
    }
  }
</script>

<style>
  .input{
    width: 300px;
  }
  .input-card{
    width: 400px;
    margin: 0px auto;
    border-radius: 10px;
  }
    .text-center {
    text-align: center;
    margin: 0.5rem
  }
</style>
