<template>
<div class="block">
    <search-card v-if="onsearch" @search="onSubmit"></search-card>
  <search-result v-if="onresultShow" @onback="onBack"></search-result>
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
        alert('submit!    ' + departure)
        this.onsearch = false
        this.onresultShow = true
      },
      onBack () {
        this.onresultShow = false
        this.onsearch = true
      }
    },
    data () {
      return {
        onsearch: true,
        onresultShow: false,
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
  }
</style>
